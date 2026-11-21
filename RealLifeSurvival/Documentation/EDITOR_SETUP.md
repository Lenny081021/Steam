# Editor-Setup für die erste Testwelt

Nach einem erfolgreichen C++-Build muss die Welt einmal im UE-Editor als binäres `.umap`-Asset erzeugt werden. Das lässt sich nicht zuverlässig als Textdatei einchecken; dafür dient das mitgelieferte Unreal-Python-Skript.

1. Das Projekt öffnen und gegebenenfalls das C++-Modul kompilieren lassen.
2. **Edit → Plugins → Python Editor Script Plugin** aktivieren und den Editor neu starten, falls der Menüpunkt zum Ausführen von Python fehlt.
3. **Tools → Execute Python Script** wählen und `Scripts/create_start_world.py` öffnen.
4. Prüfen, dass `L_StartWorld` gespeichert wurde und unter `Content/Maps` erscheint.
5. Für eine sichtbare Sonne muss am `RLSDayNightActor` die im Skript erzeugte Directional Light eingetragen sein (das Skript erledigt dies automatisch). Anschließend Play drücken.

Das Skript legt absichtlich nur lizenzfreie Engine-Primitives an. Eine Produktionswelt wird danach in getrennten Schritten mit Landscape, Water Plugin, PCG, Meshes, Materialinstanzen, Niagara und Audio erweitert.
