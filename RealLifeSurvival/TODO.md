# Nächste Entwicklungsschritte

1. UE5.8 installieren, Projektdateien generieren und den Editor-Build durchführen; auftretende versionsspezifische APIs zuerst korrigieren.
2. `create_start_world.py` ausführen und die Testwelt durch Landscape, Water, PCG-Foliage, World Partition und Nanite-Assets ersetzen.
3. UMG-Blueprints für Hauptmenü, Pause, Inventar/Drag-and-Drop, Crafting, Bauvorschau und Grafikoptionen anlegen; die C++-Components sind ihre Datenquelle.
4. Rezepte/Items aus den eingebauten Starterwerten in DataTables verschieben; Ressourcen-, Bau- und Händler-Blueprints mit Meshes versehen.
5. Drei serverautorisative Quests implementieren und Spielstände auf Gebäude, Fahrzeuge, Weltzustand und Quests erweitern.
6. Chaos-Vehicle-Pawn als erstes fahrbares Fahrzeug erstellen, dann Farming, Tiere/NavMesh und dynamisches Wetter ergänzen.
7. LAN-Listen-Server testen; erst anschließend mit gültiger Steam-App-ID/Steamworks-SDK das OnlineSubsystem Steam konfigurieren.
8. Proxies der Phase 2 im lokalen Editor durch World Partition, Landscape/Water, PCG und lizenzierte Nanite-Assets ersetzen; Verkehrsagenten um Lane-Graph, Ampeln und Chaos-Fahrzeuge erweitern.
