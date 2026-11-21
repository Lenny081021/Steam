"""Validate files staged for UE import; never modifies source assets."""
import argparse, pathlib, json
parser=argparse.ArgumentParser(); parser.add_argument("directory",type=pathlib.Path); args=parser.parse_args()
allowed={".fbx",".gltf",".glb",".png",".tga",".jpg",".jpeg",".exr",".wav"}
report={"valid":[],"rejected":[]}
for path in args.directory.rglob("*"):
    if not path.is_file(): continue
    if path.suffix.lower() not in allowed: report["rejected"].append({"file":str(path),"reason":"unsupported extension"})
    elif path.stat().st_size==0: report["rejected"].append({"file":str(path),"reason":"empty file"})
    else: report["valid"].append({"file":str(path),"bytes":path.stat().st_size})
print(json.dumps(report,indent=2)); raise SystemExit(1 if report["rejected"] else 0)
