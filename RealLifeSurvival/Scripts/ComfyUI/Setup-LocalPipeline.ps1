param(
    [string]$Root = "I:\RealLifeSurvivalAI",
    [string]$ComfyUIPath = "I:\ComfyUI",
    [string]$PythonCommand = "py"
)
$ErrorActionPreference = "Stop"
$folders = "ComfyUI","Workflows","Jobs","Maps","Vehicles","Buildings","Vegetation","Textures","Characters","Props","UnrealImports","Logs","GeneratedAssets"
foreach ($folder in $folders) { New-Item -ItemType Directory -Force -Path (Join-Path $Root $folder) | Out-Null }
$log = Join-Path $Root "Logs\setup-$(Get-Date -Format yyyyMMdd-HHmmss).log"
function Log([string]$message) { $message | Tee-Object -FilePath $log -Append }
Log "Real Life Survival local asset pipeline setup started."
if (-not (Get-Command $PythonCommand -ErrorAction SilentlyContinue)) { throw "Python launcher '$PythonCommand' was not found. Install Python 3.10+ first." }
& $PythonCommand -m venv (Join-Path $Root ".venv")
$venvPython = Join-Path $Root ".venv\Scripts\python.exe"
& $venvPython -m pip install --upgrade pip requests | Out-File $log -Append
if (Test-Path $ComfyUIPath) { Log "ComfyUI detected at $ComfyUIPath" } else { Log "WARNING: ComfyUI not found at $ComfyUIPath; no installation or existing files were changed." }
try { $gpu = & nvidia-smi --query-gpu=name,memory.total,driver_version --format=csv,noheader 2>&1; Log "NVIDIA check: $gpu" } catch { Log "WARNING: nvidia-smi unavailable; CUDA capability was not verified." }
try { $response = Invoke-RestMethod -TimeoutSec 5 -Uri "http://127.0.0.1:8188/object_info"; Log "ComfyUI API is reachable. Node types: $($response.psobject.Properties.Count)" } catch { Log "WARNING: ComfyUI API is not running on 127.0.0.1:8188. Start it locally before submitting jobs." }
Log "Setup complete. Existing models and workflows were not modified."
