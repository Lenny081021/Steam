"""Run in Unreal Editor: Tools > Execute Python Script.
Creates a reproducible 500 x 500 m Sunset City starter district using engine primitives.
It deliberately uses no third-party assets; replace primitives with licensed assets later.
"""
import unreal
import random

MAP = "/Game/Maps/L_StartWorld"
unreal.EditorLevelLibrary.new_level(MAP)

def spawn(actor_class, location, rotation=unreal.Rotator()):
    return unreal.EditorLevelLibrary.spawn_actor_from_class(actor_class, unreal.Vector(*location), rotation)

def cube(location, scale, label, color=None):
    actor = spawn(unreal.StaticMeshActor, location)
    actor.set_actor_label(label)
    actor.static_mesh_component.set_static_mesh(unreal.load_asset("/Engine/BasicShapes/Cube.Cube"))
    actor.set_actor_scale3d(unreal.Vector(*scale))
    return actor

# Essential world actors.
spawn(unreal.PlayerStart, (0, 0, 150))
sun = spawn(unreal.DirectionalLight, (0, 0, 500), unreal.Rotator(-35, -35, 0))
spawn(unreal.SkyLight, (0, 0, 400))
spawn(unreal.SkyAtmosphere, (0, 0, 0))
spawn(unreal.VolumetricCloud, (0, 0, 0))
spawn(unreal.PostProcessVolume, (0, 0, 0)).set_editor_property("unbound", True)

# 500x500m district ground, two crossing roads, sidewalks and a small park.
cube((0, 0, -50), (250, 250, 1), "SunsetState_Ground")
cube((0, 0, 0), (250, 8, .12), "Main_Street_EastWest")
cube((0, 0, 2), (8, 250, .12), "Main_Street_NorthSouth")
for x, y, sx, sy, name in [(-110,0,1.5,250,"West_Sidewalk"),(110,0,1.5,250,"East_Sidewalk"),(0,-110,250,1.5,"South_Sidewalk"),(0,110,250,1.5,"North_Sidewalk")]:
    cube((x,y,12),(sx,sy,.08),name)
cube((145,145,10),(60,60,.15),"Sunset_Park")

# Deterministic 16-building block layout; each primitive has collision and a walkable street frontage.
random.seed(81021)
building_specs = [("Apartment",-180,-160,4,4,7),("Supermarket",-130,-160,4,3,2),("Workshop",-70,-160,3,4,2),("GasStation",20,-160,5,3,1),("CarDealer",90,-160,5,3,2),("Hotel",160,-160,4,4,8),("Residence",-180,160,3,3,3),("Office",-120,160,3,4,5),("Restaurant",-55,160,3,3,2),("Store",20,160,3,3,2),("Warehouse",90,160,4,5,3),("Clinic",165,160,3,3,3),("Apartments",-180,55,3,4,5),("Apartments",160,55,3,4,5),("Garage",-180,-55,4,3,2),("Shop",160,-55,3,3,2)]
for index, (kind,x,y,sx,sy,sz) in enumerate(building_specs):
    cube((x,y,sz*100),(sx*10,sy*10,sz*100),"%02d_%s" % (index+1,kind))

resource_class = unreal.load_class(None, "/Script/RealLifeSurvival.RLSResourceNode")
merchant_class = unreal.load_class(None, "/Script/RealLifeSurvival.RLSMerchant")
day_class = unreal.load_class(None, "/Script/RealLifeSurvival.RLSDayNightActor")
vehicle_class = unreal.load_class(None, "/Script/RealLifeSurvival.RLSDriveableVehicle")
pedestrian_class = unreal.load_class(None, "/Script/RealLifeSurvival.RLSPedestrian")
tutorial_class = unreal.load_class(None, "/Script/RealLifeSurvival.RLSTutorialMarker")
for x, y in [(300,0), (500,100), (650,-150), (800,50), (950,200), (1100,-100)]:
    spawn(resource_class, (x, y, 70))
spawn(merchant_class, (-300, 0, 100))
day = spawn(day_class, (0,0,0))
day.set_editor_property("sun", sun)

# A genuine Pawn vehicle is spawned at the dealership. It is driveable after interaction.
spawn(vehicle_class, (85, -100, 90), unreal.Rotator(0, 90, 0)).set_actor_label("Tutorial_Delivery_Van")

# Ordered tutorial interaction markers: supermarket -> client -> vehicle -> delivery.
for label, location, step, prompt in [
    ("Tutorial_Supermarket", (-130,-115,80), "VISIT_SUPERMARKET", "Kaufe Lebensmittel am Supermarkt"),
    ("Tutorial_Client", (-70,-115,80), "MEET_CLIENT", "Nimm den Lieferauftrag an"),
    ("Tutorial_Vehicle", (85,-100,80), "COLLECT_VEHICLE", "Hole das Lieferfahrzeug ab"),
    ("Tutorial_Delivery", (160,105,80), "DELIVER_PACKAGE", "Liefere die Ware ab")]:
    marker = spawn(tutorial_class, location)
    marker.set_actor_label(label)
    marker.set_editor_property("step", getattr(unreal.ERLSTutorialStep, step))
    marker.set_editor_property("prompt", prompt)

# Navigation and ten lightweight pedestrians with a two-point pavement patrol.
nav = spawn(unreal.NavMeshBoundsVolume, (0,0,200))
nav.set_actor_scale3d(unreal.Vector(3,3,1))
for index in range(10):
    x = -180 + (index % 5) * 90
    y = -105 if index < 5 else 105
    npc = spawn(pedestrian_class, (x,y,100))
    npc.set_actor_label("Pedestrian_%02d" % (index + 1))
    npc.set_editor_property("patrol_points", [unreal.Vector(x-25,y,100), unreal.Vector(x+25,y,100)])

unreal.EditorLevelLibrary.save_current_level()
unreal.log("Sunset City starter district created: " + MAP)
