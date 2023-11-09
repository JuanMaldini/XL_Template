import os
import unreal
uext = ".udatasmith"

#Find your ds folder
datasmith_folder = "D:/XL Consulting AU pty Ltd/02 - FY24 PROJECTS - Documents/2024042 - Wongaburra Agecare (Woollam)/03 - 3D & 4D/3D/XL_Exported/"

#Remplace USENAME for ds file name to use
DSFileName = "CONF_2_3" + uext                                                                          

# Carpeta donde se deben crear los niveles
destination_folder = "/Game/Map/XL"
# Mapa a agregar al mundo/level
map_to_add = "/Game/Map/L_Generics"

def Start():
    
    ############################################## New Level


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


        ########################################## Save Level


        # Guarda el nivel en la ruta especificada
        unreal.EditorLevelLibrary.save_current_level()


    ############################################## Open Level


    # Abre el nuevo nivel
    unreal.EditorLevelLibrary.load_level(level_path)


    ############################################## Importar


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

    
    ############################################## Add Generics


    # Obtén una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Define la clase de transmisión de nivel (Always Loaded)
    level_streaming_class = unreal.LevelStreamingAlwaysLoaded

    # Añade el nivel de transmisión al mundo
    level_streaming = unreal.EditorLevelUtils.add_level_to_world(world, map_to_add, level_streaming_class)

    # Guardar el nivel actual
    unreal.EditorLevelLibrary.save_current_level()


    ############################################## Seleccionar


    # Obtén el editor de nivel actual
    editor_util = unreal.EditorLevelLibrary()

    # Obtén todos los actores en la escena
    todos_los_actores = editor_util.get_all_level_actors()

    # Selecciona todos los actores
    unreal.EditorLevelLibrary.set_selected_level_actors(todos_los_actores)
    print ("XL - Actors selected")


    ############################################## RunActions


    # Obtén una lista de todos los actores de la clase BP_XL_PIPELINE en el nivel
    all_actors = unreal.EditorLevelLibrary.get_all_level_actors()
    for actor in all_actors:
        if actor.get_name() == 'BP_XL_Actions':
            # Aquí tienes tu actor, puedes hacer lo que necesites con él
            print("XL - " + actor)

    actor.call_method("XL_RUN")


    ############################################## Select cam


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

def RunActions():                   # RunActions


    ####################### Seleccionar


    # Obtén el editor de nivel actual
    editor_util = unreal.EditorLevelLibrary()

    # Obtén todos los actores en la escena
    todos_los_actores = editor_util.get_all_level_actors()

    # Selecciona todos los actores
    unreal.EditorLevelLibrary.set_selected_level_actors(todos_los_actores)
    print ("XL - Actors selected")


    ####################### RunActions


    # Obtén una lista de todos los actores de la clase BP_XL_PIPELINE en el nivel
    all_actors = unreal.EditorLevelLibrary.get_all_level_actors()
    for actor in all_actors:
        if actor.get_name() == 'BP_XL_Actions':
            # Aquí tienes tu actor, puedes hacer lo que necesites con él
            print("XL - " + actor)

    actor.call_method("XL_RUN")

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

def AddGenerics():


    ############################################## Add Generics


    # Obtén una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Define la clase de transmisión de nivel (Always Loaded)
    level_streaming_class = unreal.LevelStreamingAlwaysLoaded

    # Añade el nivel de transmisión al mundo
    level_streaming = unreal.EditorLevelUtils.add_level_to_world(world, map_to_add, level_streaming_class)

    # Guardar el nivel actual
    unreal.EditorLevelLibrary.save_current_level()
    
def MetaRender():


    # Asegúrate de que la ruta al EUW es correcta, incluyendo el nombre del asset al final
    widget_blueprint_path = "/Game/XL_MetaShoot"

    # Cargar el Editor Utility Widget Blueprint
    asset_library = unreal.EditorAssetLibrary
    widget_blueprint = asset_library.load_asset(widget_blueprint_path)

    if widget_blueprint is None:
        unreal.log_error("XL - No se pudo cargar el Editor Utility Widget desde: {}".format(widget_blueprint_path))
        return

    # Obtener la clase del Editor Utility Widget Blueprint
    widget_class = getattr(widget_blueprint, 'GeneratedClass', None)

    if widget_class is None:
        unreal.log_error("XL - No se pudo obtener la clase del Editor Utility Widget desde: {}".format(widget_blueprint_path))
        return

    # Obtén el Editor Utility Subsystem
    editor_utility_subsystem = unreal.EditorUtilityLibrary.get_editor_utility_subsystem()

    # Crear una instancia del Editor Utility Widget
    try:
        widget_instance = editor_utility_subsystem.spawn_and_register_tab(widget_class)
        
        # Verifica si la instancia del widget está abierta y si no, ábrela.
        if not widget_instance.is_opened():
            widget_instance.open_requested()
        
        # Ejecuta la función dentro del EUW
        widget_instance.call_function('XLFunction')
        
        unreal.log("XL - La función 'XLFunction' fue llamada con éxito.")
    except Exception as e:
        unreal.log_error("XL - Hubo un error al crear la instancia del widget o al llamar a la función: {}".format(e))

def MetaRendesr():
    
    widget_blueprint_path = "/Game/XL_MetaShoot.XL_MetaShoot_C"

    
    # Cargar la clase del Editor Utility Widget usando la ruta proporcionada.
    widget_class = unreal.EditorAssetLibrary.load_blueprint_class(widget_blueprint_path)

    # Verificar si la clase del widget se cargó correctamente.
    if not widget_class or not issubclass(widget_class, unreal.EditorUtilityWidget):
        unreal.log_error(f"XL - No se pudo cargar la clase del Editor Utility Widget desde: {widget_blueprint_path}")
        return

    # Crear una instancia del widget en el editor.
    try:
        # Abre la instancia del widget como una pestaña en el editor.
        widget_instance = unreal.EditorUtilitySubsystem.spawn_and_register_tab(widget_class)()
        
        # En este punto, el widget se ha abierto con éxito.
        unreal.log("XL - El widget ha sido abierto con éxito.")
    except Exception as e:
        unreal.log_error