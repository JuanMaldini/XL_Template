import os
import unreal
uext = ".udatasmith"

#Find your ds folder
datasmith_folder = "C:/Dropbox/Projects/XL/01 - Model/LiveLinkTest_V03/XL_Exported/"

#Remplace USENAME for ds file name to use
DSFileName = "Escena1" + uext                                                                          

# Carpeta donde se deben crear los niveles
destination_folder = "/Game/Map/XL"
# Mapa a agregar al mundo/level
map_to_add = "/Game/Map/L_Generics"

def Start():
    
    ####################### New Level


    # Obtiene una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Obtiene el nombre del nivel a partir del nombre del archivo
    level_name = DSFileName.split('.')[0]
    print("XL - Level name: " + level_name)

    level_path = destination_folder + "/" + level_name
    print("XL - Level path:" + level_path)

    # Verifica si el nivel ya existe
    if unreal.EditorAssetLibrary.does_asset_exist(level_path):
        print(f"XL - El nivel ya existe: {level_path}")
    else:
        # Crea un nuevo nivel vacío
        new_level = unreal.EditorLevelLibrary.new_level(level_path)


        ################### Save Level


        # Guarda el nivel en la ruta especificada
        unreal.EditorLevelLibrary.save_current_level()


    ####################### Open Level


    # Abre el nuevo nivel
    unreal.EditorLevelLibrary.load_level(level_path)


    ####################### Importar


    ds_file_on_disk = datasmith_folder + "/" + DSFileName
    ds_scene_in_memory = unreal.DatasmithSceneElement.construct_datasmith_scene_from_file(ds_file_on_disk)

    if ds_scene_in_memory is None:
        print ("XL - Scene loading failed.")
        print (ds_file_on_disk)
        quit()

    # Modify the data in the scene to filter out or combine elements...

    # Remove any mesh whose name includes a certain keyword.
    remove_keyword = "exterior"      # we'll remove any actors with this string in their names.
    meshes_to_skip = set([])         # we'll use this set to temporarily store the meshes we don't need.

    # Remove from the scene any mesh actors whose names match the string set above.
    for mesh_actor in ds_scene_in_memory.get_all_mesh_actors():
        actor_label = mesh_actor.get_label()
        if remove_keyword in actor_label:
            print("XL - Removing actor named: " + actor_label)
            # add this actor's mesh asset to the list of meshes to skip
            mesh = mesh_actor.get_mesh_element()
            meshes_to_skip.add(mesh)
            ds_scene_in_memory.remove_mesh_actor(mesh_actor)

    # Remove all the meshes we don't need to import.
    for mesh in meshes_to_skip:
        mesh_name = mesh.get_element_name()
        print("XL - Removing mesh named " + mesh_name)
        ds_scene_in_memory.remove_mesh(mesh)

    # Set import options.
    import_options = ds_scene_in_memory.get_options(unreal.DatasmithImportOptions)
    import_options.base_options.scene_handling = unreal.DatasmithImportScene.CURRENT_LEVEL

    # Finalize the process by creating assets and actors.

    # Your destination folder must start with /Game/
    result = ds_scene_in_memory.import_scene(destination_folder)

    if not result.import_succeed:
        print ("XL - Importing failed.")
        quit()

    # Clean up the Datasmith Scene.
    ds_scene_in_memory.destroy_scene()
    print ("XL - Custom import process complete!")

    
    ####################### Add Generics


    # Obtén una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Define la clase de transmisión de nivel (Always Loaded)
    level_streaming_class = unreal.LevelStreamingAlwaysLoaded

    # Añade el nivel de transmisión al mundo
    level_streaming = unreal.EditorLevelUtils.add_level_to_world(world, map_to_add, level_streaming_class)

    # Guardar el nivel actual
    unreal.EditorLevelLibrary.save_current_level()


    ####################### Seleccionar


    # Obtén el editor de nivel actual
    editor_util = unreal.EditorLevelLibrary()

    # Obtén todos los actores en la escena
    todos_los_actores = editor_util.get_all_level_actors()

    # Selecciona todos los actores
    unreal.EditorLevelLibrary.set_selected_level_actors(todos_los_actores)
    print ("XL - Actors selected")


    ####################### RunActions


    # Carga el Blueprint
    blueprint_path = "/Game/Blueprint/Dataprep/EUB/BP_XL_Actions.BP_XL_Actions"
    blueprint_class = unreal.EditorAssetLibrary.load_blueprint_class(blueprint_path)

    # Crea una instancia del Blueprint
    blueprint_instance = blueprint_class()

    # Ejecuta el evento personalizado
    blueprint_instance.RUN_XL_ACTIONS()

#def SaveAll():                      # Save all

def RunActions():


    ####################### Seleccionar


    # Obtén el editor de nivel actual
    editor_util = unreal.EditorLevelLibrary()

    # Obtén todos los actores en la escena
    todos_los_actores = editor_util.get_all_level_actors()

    # Selecciona todos los actores
    unreal.EditorLevelLibrary.set_selected_level_actors(todos_los_actores)
    print ("XL - Actors selected")


    ####################### RunActions


    # Obtiene el objeto de contexto del mundo
    world = unreal.UnrealEditorSubsystem().get_editor_world()

    # Primero, obtén tu Blueprint. En este caso, lo obtendremos a través de su ruta
    bp_asset_path = "/Game/Blueprint/Dataprep/EUB/BP_XL_Actions"
    bp_asset = unreal.EditorAssetLibrary.load_asset(bp_asset_path)

    # Luego, obtén su clase generada como una ruta de cadena y cárgala
    bp_class = unreal.load_object(None, bp_asset.generated_class().get_path_name())

    # Finalmente, obtén el objeto predeterminado, que es el objeto desde el cual podemos llamar a una función o modificar una propiedad
    bp_cdo = unreal.get_default_object(bp_class)

    # Para llamar a una función
    # El primer argumento es el nombre de la función
    # El segundo son los argumentos, que se pasan como una única tupla
    # El tercero son los kwargs, que se pasan como un único diccionario
    # Es posible que se necesite el mundo, también parece ser siempre el último de los argumentos
    bp_cdo.call_method("XL_RUN", (world,), {})

    # Para modificar una propiedad
    # Usa set_editor_property
    # bp_cdo.set_editor_property("PropName", value)

def SelectAll():                    # Select all actor of level
    
    # Obtén el editor de nivel actual
    editor_util = unreal.EditorLevelLibrary()

    # Obtén todos los actores en la escena
    todos_los_actores = editor_util.get_all_level_actors()

    # Selecciona todos los actores
    unreal.EditorLevelLibrary.set_selected_level_actors(todos_los_actores)
    print ("XL - Actors selected")

def SelectCamByLevelName():         # Select cam = level

    # Obtén el nivel actual
    editor_level_lib = unreal.EditorLevelLibrary()
    current_level = editor_level_lib.get_editor_world()
    print(f"XL - Nivel actual: {current_level.get_name()}")

    # Obtén todos los actores del nivel
    actors = unreal.EditorLevelLibrary.get_all_level_actors()
    print(f"XL - Total de actores en el nivel: {len(actors)}")

    # Filtra solo los actores de tipo CineCameraActor
    cine_actors = [actor for actor in actors if isinstance(actor, unreal.CineCameraActor)]
    print(f"XL - Total de CineCameraActors en el nivel: {len(cine_actors)}")

    # Encuentra la CineCameraActor con el mismo nombre que el nivel actual
    for actor in cine_actors:
        if actor.get_actor_label() == current_level.get_name():
            selected_actor = actor
            print(f"XL - CineCameraActor seleccionada: {selected_actor.get_actor_label()}")

            # Selecciona la CineCameraActor en el editor
            unreal.EditorLevelLibrary.set_selected_level_actors([selected_actor])
            break

def SelectCamByDs():                # Select cam = datasmith

    # Obtén todos los actores en la escena
    todos_los_actores = unreal.EditorLevelLibrary.get_all_level_actors()

    # Busca el Datasmith Scene Actor
    for actor in todos_los_actores:
        if actor.get_class().get_name() == 'DatasmithSceneActor':
            nombre_de_escena = actor.get_actor_label()
            print("XL - Nombre de la escena: " + nombre_de_escena)
            break

    # Busca la cámara con el mismo nombre que el Datasmith Scene Actor
    for actor in todos_los_actores:
        if actor.get_class().get_name() == 'CineCameraActor':
            nombre_camara = actor.get_actor_label()

            if nombre_camara == nombre_de_escena:
                # Selecciona la cámara
                unreal.EditorLevelLibrary.set_selected_level_actors([actor])
                print("XL - Cámara seleccionada: " + nombre_camara)
                break
