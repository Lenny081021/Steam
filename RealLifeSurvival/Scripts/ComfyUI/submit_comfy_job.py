"""Submit an existing, user-reviewed ComfyUI API workflow to a local API.
No model or node names are assumed; the workflow must already be exported by ComfyUI.
"""
import argparse, json, pathlib, urllib.request

parser = argparse.ArgumentParser()
parser.add_argument("workflow", type=pathlib.Path, help="ComfyUI API-format workflow JSON")
parser.add_argument("--api", default="http://127.0.0.1:8188")
parser.add_argument("--job-name", default="rls_asset_job")
args = parser.parse_args()
workflow = json.loads(args.workflow.read_text(encoding="utf-8"))
payload = json.dumps({"prompt": workflow, "client_id": args.job_name}).encode("utf-8")
request = urllib.request.Request(args.api.rstrip("/") + "/prompt", data=payload, headers={"Content-Type":"application/json"})
try:
    with urllib.request.urlopen(request, timeout=20) as response: print(response.read().decode("utf-8"))
except OSError as error:
    raise SystemExit("ComfyUI job was not submitted: %s" % error)
