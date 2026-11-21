# REAL LIFE SURVIVAL

Unreal-Engine-C++-Projekt für eine erste spielbare Survival-Sandbox unter Windows. Es ist kein HTML-Ersatz und enthält ausschließlich native UE-Projektdateien.

## Stand

Die C++-Basis implementiert: First-/Third-Person-Steuerung, Interaktion, replizierbares Inventar, Survival-Werte, Ressourcen, Händler/Geld, Crafting, Bauen, Spielstand-Grundlagen, Tag/Nacht und einen lokalen, fahrbaren Fahrzeugprototyp mit Ein-/Aussteigen, Kamera, Tank und replizierter Steuerung. Das Stadt-Editor-Skript erzeugt ein 500×500-m-Sunset-City-Viertel mit 16 Gebäuden, Straßen, Park, Fahrzeug, Navigation und zehn einfachen Fußgängerpatrouillen. Das Tutorial führt über vier echte Interaktionsmarker zu einer Lieferbelohnung.

Die Inhalte werden bewusst ohne fremde kommerzielle Assets erzeugt. Engine-Grundformen dienen dem ersten Testlevel als sichtbare Objekte.

## Voraussetzungen

- Unreal Engine **5.8** für Windows (bei abweichender UE5-Version `EngineAssociation` in `RealLifeSurvival.uproject` anpassen)
- Visual Studio 2022 mit *Desktop development with C++* und *Game development with C++*
- Windows 11 / DirectX 12

## Öffnen und bauen

1. Unreal Engine installieren und `RealLifeSurvival.uproject` per Rechtsklick **Generate Visual Studio project files** wählen.
2. Die erzeugte `RealLifeSurvival.sln` in Visual Studio öffnen und `Development Editor | Win64` bauen.
3. Das Projekt im Unreal Editor öffnen. Bei fehlenden C++-Klassen zuerst den erfolgreichen Editor-Build abwarten.
4. Unter **Tools → Execute Python Script** die Datei `Scripts/create_start_world.py` ausführen. Sie erstellt `Content/Maps/L_StartWorld.umap` als 500×500-m-Stadtviertel mit Straßen, Gebäuden, Park, Navigation, NPCs, Ressourcen, Händler, Tutorial-Markern, Fahrzeug und Tag/Nacht-Aktor.
5. `L_StartWorld` öffnen und Play drücken.

## Testablauf

- `WASD`, Maus, Leertaste, Shift und Strg bewegen den Spieler.
- `C` wechselt Perspektive; `E` sammelt Ressourcen oder verkauft am Händler.
- `P` wandelt 2 Holz in ein Brett um. In dieser Starterfassung können Daten-Tabellen die Rezepte später ersetzen.
- `B` platziert eine Wand aus vier Brettern; das Netzwerksystem prüft Reichweite und zieht die Kosten ausschließlich auf dem Server ab.
- `F` verbraucht ein Item mit der Kennung `Food`.
- Am Fahrzeug: `E` ein-/aussteigen, `WASD` fahren/lenken, Leertaste Motor an/aus. Das ist ein funktionaler, kinematischer C++-Prototyp; die Chaos-Umsetzung erfordert ein importiertes Skeletal-Chassis und getrennte Räder.
- Tutorial: Am Supermarkt, Auftraggeber, Fahrzeug-Abholung und Lieferziel nacheinander `E` drücken. Nach der Lieferung werden 500 € gutgeschrieben.

## Daten und Erweiterung

`FRLSItemDefinition` und `FRLSRecipeDefinition` sind DataTable-Zeilenstrukturen. Weist man am Inventory- bzw. Crafting-Component eine DataTable zu, überschreibt sie die eingebauten Starterwerte. Für eine vollwertige UMG-Oberfläche und grafische Asset-Pipeline können Blueprint-Unterklassen der C++-Klassen angelegt werden.

## Nicht als fertig ausgegeben

Noch offen sind unter anderem: vollständige UMG-Menü-/Inventar-Drag-and-Drop-Ansichten, Map-/Wasser-/Landschafts-Assets, ein Chaos-Vehicle mit Skeletal-Mesh-Physik, Verkehr-KI, Landwirtschaft, Tiere/KI, Wettereffekte, Speicherstände für alle Weltobjekte/Fahrzeuge, Steam OnlineSubsystem sowie ein Windows-Paket. Details und Reihenfolge stehen in `TODO.md`.

## Lokale ComfyUI-Pipeline

Die nur lokal ausführbaren Windows-Werkzeuge stehen unter `Scripts/ComfyUI/`. Anleitung: [Scripts/ComfyUI/README.md](Scripts/ComfyUI/README.md). Sie prüfen ComfyUI und GPU, erzeugen die Ordnerstruktur unter `I:\RealLifeSurvivalAI` und senden ausschließlich bereits im lokalen ComfyUI getestete API-Workflows ab.

## Phase 2: Stadt- und Asset-Erweiterung

Zusätzliche Editor-Erzeugung und RTX-3070-Profile: [Documentation/PHASE2_SETUP.md](Documentation/PHASE2_SETUP.md). Die Erweiterung erzeugt keine vermeintlich fertigen AAA-Assets: Straßen, Gebäude, Wasser, Vegetation und Verkehr sind reproduzierbare, funktionale Engine-Proxies, die anschließend kontrolliert durch lokale Unreal-/ComfyUI-Assets ersetzt werden.

## Prüfung

In der bereitgestellten Umgebung war keine Unreal-Engine-Installation bzw. kein `UnrealBuildTool` auffindbar. Deshalb konnte hier kein Editor- oder Windows-Build ehrlich ausgeführt werden. Nach der obigen Installation ist der erste verbindliche Prüfpunkt ein `Development Editor | Win64`-Build.
