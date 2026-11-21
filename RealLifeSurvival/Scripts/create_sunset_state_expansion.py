"""UE Editor Python: extend L_StartWorld into a reproducible 2 x 2 km playable test region.
Run after create_start_world.py. Uses only Engine BasicShapes and native RLS actor classes.
"""
import random
import unreal

SEED = 81022
random.seed(SEED)

def spawn(cls, pos, rot=unreal.Rotator()):
    return unreal.EditorLevelLibrary.spawn_actor_from_class(cls, unreal.Vector(*pos), rot)

def cube(name, pos, scale):
    a = spawn(unreal.StaticMeshActor, pos)
    a.set_actor_label(name)
    a.static_mesh_component.set_static_mesh(unreal.load_asset("/Engine/BasicShapes/Cube.Cube"))
    a.set_actor_scale3d(unreal.Vector(*scale))
    return a

# Large continuous ground and a clear arterial grid. Units are centimeters.
cube("SunsetState_Terrain", (0,0,-120), (1000,1000,1))
roads = [(-600,0,1000,10), (0,0,1000,10), (600,0,1000,10), (0,-600,10,1000), (0,0,10,1000), (0,600,10,1000)]
for i,(x,y,sx,sy) in enumerate(roads): cube("Arterial_%02d" % i,(x,y,5),(sx,sy,.15))

# Five districts correspond to the Sunset State plan. Each has collision, a block street and 12 buildings.
districts = {"SunsetCity":(0,0),"PalmBeach":(0,-850),"GreenValley":(-850,0),"RockyMountains":(-850,850),"IndustrialHarbor":(850,850)}
for name,(cx,cy) in districts.items():
    cube(name+"_Plaza",(cx,cy,15),(170,170,.2))
    for index in range(12):
        x = cx + ((index % 4)-1.5)*75
        y = cy + ((index // 4)-1)*90
        floors = 2 + (index % 5)
        cube("%s_Building_%02d" % (name,index+1),(x,y,floors*90),(25,28,floors*90))

# Interior shells: open front/side walls, floor and roof inside the starter apartment block.
for pos,scale,name in [((-210,-160,15),(25,25,.12),"ApartmentInteriorFloor"),((-235,-160,110),(.12,25,1.1),"ApartmentInteriorWallW"),((-185,-160,110),(.12,25,1.1),"ApartmentInteriorWallE"),((-210,-185,110),(25,.12,1.1),"ApartmentInteriorWallN"),((-210,-160,220),(25,25,.12),"ApartmentInteriorRoof")]: cube(name,pos,scale)

# Water plane and simple vegetation proxy clusters. Replace with Water/PCG assets during art production.
water=cube("PalmBeach_Water",(500,-850,-20),(350,130,.05)); water.set_actor_label("PalmBeach_Water_Placeholder")
for i in range(120):
    x=random.randint(-980,980); y=random.randint(-980,980)
    if abs(x)%600 > 40 and abs(y)%600 > 40: cube("VegetationProxy_%03d"%i,(x,y,80),(2,2,8))

traffic_class=unreal.load_class(None,"/Script/RealLifeSurvival.RLSTrafficVehicle")
for i in range(12):
    x=-500+i*90
    v=spawn(traffic_class,(x,-40,60),unreal.Rotator(0,0,0))
    v.set_actor_label("TrafficVehicle_%02d"%(i+1))
    v.set_editor_property("route_points",[unreal.Vector(-900,-40,60),unreal.Vector(900,-40,60),unreal.Vector(900,40,60),unreal.Vector(-900,40,60)])

property_class=unreal.load_class(None,"/Script/RealLifeSurvival.RLSProperty")
p=spawn(property_class,(-210,-160,80)); p.set_actor_label("Starter_Apartment_ForSale"); p.set_editor_property("property_name","Sunset City Apartment"); p.set_editor_property("purchase_price",50000)
unreal.EditorLevelLibrary.save_current_level()
unreal.log("Sunset State expansion generated with seed %d" % SEED)
