# Lokale ComfyUI-Asset-Pipeline

Diese Werkzeuge sprechen ausschließlich mit `http://127.0.0.1:8188` auf dem Windows-PC. Die Cloud greift nicht auf die lokale API zu.

1. PowerShell öffnen und `Set-ExecutionPolicy -Scope Process Bypass` verwenden, falls die lokale Richtlinie Skripte blockiert.
2. `./Setup-LocalPipeline.ps1 -Root I:\RealLifeSurvivalAI -ComfyUIPath I:\ComfyUI` ausführen.
3. In ComfyUI ein getestetes Workflow-Graph mit den **lokal vorhandenen** Nodes/Modellen erstellen und im API-Format speichern. Das Tool erfindet keine Modellnamen, PBR-Kanäle oder Image-to-3D-Nodes.
4. `I:\RealLifeSurvivalAI\.venv\Scripts\python.exe submit_comfy_job.py <workflow-api.json> --job-name asphalt_001` ausführen.

Für eine RTX 3070 mit 8 GB VRAM zunächst 1024px-Texturen, Batchgröße 1 und normale Präzision verwenden. Ein Bild ist kein verwendbares 3D-Fahrzeug: Mesh, separate Räder, Kollisionsformen, UVs, Skalierung und LODs müssen vor dem Unreal-Import separat geprüft werden.
