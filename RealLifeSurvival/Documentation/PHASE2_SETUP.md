# Phase 2 – Lokale Unreal-Erzeugung

1. Erst `Scripts/create_start_world.py` ausführen.
2. Dann `Scripts/create_sunset_state_expansion.py` im selben geöffneten Level ausführen. Das erzeugt den reproduzierbaren 2×2-km-Testbereich mit fünf Distrikt-Proxies, Straßennetz, Innenraumschale, Wasserfläche, Vegetations-Proxies, zwölf Verkehrsfahrzeugen und einer kaufbaren Immobilie.
3. Für Produktionsqualität die Proxies durch Landscape, Water, PCG, Nanite-Meshes und World Partition ersetzen. Das kann erst im installierten UE-Editor als Binär-Assets gespeichert werden.

## RTX 3070

`Config/DefaultScalability.ini` definiert niedrige, mittlere, hohe und Ultra-Scalability-Stufen. Für 1080p zunächst **High** verwenden. Das Projekt enthält keine behauptete FPS-Messung; `stat unit`, `stat gpu` und Unreal Insights sind beim lokalen Test zu erfassen.

## Fahrzeug-Assets

Der C++-Prototyp ist fahrbar, verwendet aber noch keine Chaos-Räder. Vor der Umstellung müssen die in `Scripts/AssetTools/vehicle_import_manifest.json` beschriebenen Komponenten vorhanden und geprüft sein. `validate_unreal_assets.py I:\RealLifeSurvivalAI\UnrealImports` prüft nur Dateitypen/Leere und ersetzt keine fachliche Mesh-Prüfung.
