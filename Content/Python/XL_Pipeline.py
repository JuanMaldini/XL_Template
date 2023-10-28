import os
import unreal
uext = ".udatasmith"
 






#Find your ds folder
datasmith_folder = "C:/Dropbox/Projects/XL/01 - Model/LiveLinkTest_V03/XL_Exported/"
DSFileName = "Escena1" + uext           #Remplace USENAME for ds file name to use
































# Carpeta donde se deben crear los niveles
destination_folder = "/Game/Map/XL"
# Mapa a agregar al mundo/level
map_to_add = "/Game/Map/L_Generics"

def XL():
    
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


    ####################### Seleccionar


    # Obtén el editor de nivel actual
    editor_util = unreal.EditorLevelLibrary()

    # Obtén todos los actores en la escena
    todos_los_actores = editor_util.get_all_level_actors()

    # Selecciona todos los actores
    unreal.EditorLevelLibrary.set_selected_level_actors(todos_los_actores)
    print ("XL - Actors selected")

def Generics():


    ####################### Add Generics


    # Obtén una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Define la clase de transmisión de nivel (Always Loaded)
    level_streaming_class = unreal.LevelStreamingAlwaysLoaded

    # Añade el nivel de transmisión al mundo
    level_streaming = unreal.EditorLevelUtils.add_level_to_world(world, map_to_add, level_streaming_class)

    # Guardar el nivel actual
    unreal.EditorLevelLibrary.save_current_level()
    
    
    ####################### Select Camera


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


    ####################### Select Camera


    # Guarda el nivel en la ruta especificada
    unreal.EditorLevelLibrary.save_current_level()

def SelectAll():
    # Obtén el editor de nivel actual
    editor_util = unreal.EditorLevelLibrary()

    # Obtén todos los actores en la escena
    todos_los_actores = editor_util.get_all_level_actors()

    # Selecciona todos los actores
    unreal.EditorLevelLibrary.set_selected_level_actors(todos_los_actores)
    print ("XL - Actors selected")
































####################### old func

def ImportDS():                     # Import in new Level #Fix All Save

    # Obtiene una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Obtiene la lista de archivos Datasmith en la carpeta
    datasmith_files = [f for f in os.listdir(datasmith_folder) if f.endswith(".udatasmith")]    
    
    for ds_file in datasmith_files:

        # Archivo Datasmith a importar
        ds_file_on_disk = (datasmith_folder + ds_file)
        print ("XL - Importando " + ds_file_on_disk)

        ds_scene_in_memory = unreal.DatasmithSceneElement.construct_datasmith_scene_from_file(ds_file_on_disk)

        if ds_scene_in_memory is None:
            print ("XL - Scene loading failed.")
            quit()

        # Modify the data in the scene to filter out or combine elements...

        # Remove any mesh whose name includes a certain keyword.
        remove_keyword = "exterior"      # we'll remove any actors with this string in their names.
        meshes_to_skip = set([])         # we'll use this set to temporarily store the meshes we don't need.

        # Remove from the scene any mesh actors whose names match the string set above.
        for mesh_actor in ds_scene_in_memory.get_all_mesh_actors():
            actor_label = mesh_actor.get_label()
            if remove_keyword in actor_label:
                print("XL - removing actor named: " + actor_label)
                # add this actor's mesh asset to the list of meshes to skip
                mesh = mesh_actor.get_mesh_element()
                meshes_to_skip.add(mesh)
                ds_scene_in_memory.remove_mesh_actor(mesh_actor)

        # Remove all the meshes we don't need to import.
        for mesh in meshes_to_skip:
            mesh_name = mesh.get_element_name()
            print("XL - removing mesh named " + mesh_name)
            ds_scene_in_memory.remove_mesh(mesh)

        # Set import options.
        import_options = ds_scene_in_memory.get_options(unreal.DatasmithImportOptions)
        import_options.base_options.scene_handling = unreal.DatasmithImportScene.ASSETS_ONLY

        # Finalize the process by creating assets and actors.

        # Your destination folder must start with /Game/
        result = ds_scene_in_memory.import_scene(destination_folder)

        if not result.import_succeed:
            print ("XL - Importing failed.")
            quit()

        # Clean up the Datasmith Scene.
        ds_scene_in_memory.destroy_scene()
        print ("XL - Custom import process complete!")

def CreateAllLevels():              # Create every LS by DS in folder

    # Obtiene una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Obtiene la lista de archivos Datasmith en la carpeta
    datasmith_files = [f for f in os.listdir(datasmith_folder) if f.endswith(".udatasmith")]

    for ds_file in datasmith_files:

        # Obtiene el nombre del nivel a partir del nombre del archivo
        level_name = os.path.splitext(os.path.basename(ds_file))[0]
        print("XL - Level name: " + level_name)
        level_path = destination_folder + "/" + level_name
        print("XL - Level path:" + level_path)

        # Verifica si el nivel ya existe
        if unreal.EditorAssetLibrary.does_asset_exist(level_path):
            print(f"XL - El nivel ya existe: {level_path}")
            continue

        # Crea un nuevo nivel
        new_level = unreal.EditorLevelUtils.create_new_streaming_level(unreal.LevelStreamingDynamic, level_path, True)
        if new_level is None:
            print(f"XL - Error al crear el nivel: {level_name}")
            continue

        # Guarda el nuevo nivel
        save_success = unreal.EditorAssetLibrary.save_asset(level_path)
        if not save_success:
            print(f"XL - Error al guardar el nivel: {level_name}")

        # Agrega el nivel al mundo
        #world.add_actor(new_level.get_world())
        print(f"XL - Nivel creado y agregado al mundo: {level_name}")

def AddGenerics():                  # Add L_Generics Lighting setup to the levels in destination_folder
    
    # Obtén una lista de niveles en la carpeta de destino
    levels_in_destination = unreal.EditorAssetLibrary.list_assets(destination_folder)

    # Recorre cada nivel en la carpeta
    for level_path in levels_in_destination:
        # Carga el nivel
        level = unreal.EditorLevelLibrary.load_level(level_path)

        if level:
            # Obtén una referencia al mundo actual
            world = unreal.EditorLevelLibrary.get_editor_world()
            
            # Define la clase de transmisión de nivel (Always Loaded)
            level_streaming_class = unreal.LevelStreamingAlwaysLoaded

            # Añade el nivel de transmisión al mundo
            level_streaming = unreal.EditorLevelUtils.add_level_to_world(world, map_to_add, level_streaming_class)

            if level_streaming:
                print(f"XL - Nivel añadido con éxito a: {level_path}")
                
                # Guardar el nivel actual
                unreal.EditorLevelLibrary.save_current_level()

def AddDs():                        # NO #Add Ds to the world

    # Obtén una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()
    # Obtén el nombre del nivel actual
    level_name = world.get_name()
    print(f"XL - Nombre del nivel actual: {level_name}")
    
    # Recorre solo los archivos en la carpeta de importación
    for file in os.listdir(destination_folder):
        if file.endswith(".udatasmith"):  # Solo procesa archivos con la extensión .umap
            print("XL - " + destination_folder)

            # Obtiene el nombre base del archivo (sin la extensión)
            file_name = os.path.splitext(file)[0]
            print(f"XL - Nombre del archivo: {file_name}")
            # Compara el nombre del archivo con el nombre del nivel
            if file_name == level_name:
                print("XL - El nombre del archivo coincide con el nombre del nivel.")
                # Si coincide, añade el archivo al nivel
                file_path = os.path.join(destination_folder, file)
                print("XL - file_path " + file_path)
                file_asset = unreal.EditorAssetLibrary.load_asset(file_path)
                print("XL - file_asset " + file_asset)
                unreal.EditorLevelUtils.add_level_to_world(world, file_asset)
                print("XL - El archivo ha sido añadido al nivel.")
                # Guarda el nivel actual
                unreal.EditorLevelLibrary.save_current_level()
                print("XL - Nivel guardado con éxito.")

def SelectCamByLevelName():         # Select Cam = Level
    
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

def SelectCamByDs():                # Select Cam = Datasmith
    
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

def Actions():                      # NO # Excecute XL_Actions
    
    # Crea una instancia de EditorUtilityObject
    EditorUtilityObject = unreal.EditorUtilityObject()
    # Ejecuta el método run() en la instancia
    EditorUtilityObject.run()

def Render():                       # NO # Plugin #Find level name > camera > render
    print("XL - Renderizado.")

def Start():

##################                  # ImportDS

    # Obtiene una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Obtiene la lista de archivos Datasmith en la carpeta
    datasmith_files = [f for f in os.listdir(datasmith_folder) if f.endswith(".udatasmith")]    
    
    for ds_file in datasmith_files:

        # Archivo Datasmith a importar
        ds_file_on_disk = (datasmith_folder + ds_file)
        print ("XL - Importando " + ds_file_on_disk)

        ds_scene_in_memory = unreal.DatasmithSceneElement.construct_datasmith_scene_from_file(ds_file_on_disk)

        if ds_scene_in_memory is None:
            print ("XL - Scene loading failed.")
            quit()

        # Modify the data in the scene to filter out or combine elements...

        # Remove any mesh whose name includes a certain keyword.
        remove_keyword = "exterior"      # we'll remove any actors with this string in their names.
        meshes_to_skip = set([])         # we'll use this set to temporarily store the meshes we don't need.

        # Remove from the scene any mesh actors whose names match the string set above.
        for mesh_actor in ds_scene_in_memory.get_all_mesh_actors():
            actor_label = mesh_actor.get_label()
            if remove_keyword in actor_label:
                print("XL - removing actor named: " + actor_label)
                # add this actor's mesh asset to the list of meshes to skip
                mesh = mesh_actor.get_mesh_element()
                meshes_to_skip.add(mesh)
                ds_scene_in_memory.remove_mesh_actor(mesh_actor)

        # Remove all the meshes we don't need to import.
        for mesh in meshes_to_skip:
            mesh_name = mesh.get_element_name()
            print("XL - removing mesh named " + mesh_name)
            ds_scene_in_memory.remove_mesh(mesh)

        # Set import options.
        import_options = ds_scene_in_memory.get_options(unreal.DatasmithImportOptions)
        import_options.base_options.scene_handling = unreal.DatasmithImportScene.ASSETS_ONLY

        # Finalize the process by creating assets and actors.

        # Your destination folder must start with /Game/
        result = ds_scene_in_memory.import_scene(destination_folder)

        if not result.import_succeed:
            print ("XL - Importing failed.")
            quit()

        # Clean up the Datasmith Scene.
        ds_scene_in_memory.destroy_scene()
        print ("XL - Custom import process complete!")

##################                  # CreateLevels

    # Obtiene una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Obtiene la lista de archivos Datasmith en la carpeta
    datasmith_files = [f for f in os.listdir(datasmith_folder) if f.endswith(".udatasmith")]

    for ds_file in datasmith_files:

        # Obtiene el nombre del nivel a partir del nombre del archivo
        level_name = os.path.splitext(os.path.basename(ds_file))[0]
        print("XL - Level name: " + level_name)
        level_path = destination_folder + "/" + level_name
        print("XL - Level path:" + level_path)

        # Verifica si el nivel ya existe
        if unreal.EditorAssetLibrary.does_asset_exist(level_path):
            print(f"XL - El nivel ya existe: {level_path}")
            continue

        # Crea un nuevo nivel
        new_level = unreal.EditorLevelUtils.create_new_streaming_level(unreal.LevelStreamingDynamic, level_path, True)
        if new_level is None:
            print(f"XL - Error al crear el nivel: {level_name}")
            continue

        # Guarda el nuevo nivel
        save_success = unreal.EditorAssetLibrary.save_asset(level_path)
        if not save_success:
            print(f"XL - Error al guardar el nivel: {level_name}")

        # Agrega el nivel al mundo
        #world.add_actor(new_level.get_world())
        print(f"XL - Nivel creado y agregado al mundo: {level_name}")

def AddSelected():
    
    # Obtiene la selección actual en el Content Browser
    selected_assets = unreal.EditorUtilityLibrary.get_selected_assets()

    # Obtiene una referencia al mundo actual
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Obtiene una referencia al nivel actual
    current_level = world.get_current_level()

    # Verifica si hay un nivel actual y activos seleccionados
    if current_level and selected_assets:
        for selected_asset in selected_assets:
            # Crea un nuevo actor en el nivel actual con la colisión forzada (ALWAYS_SPAWN)
            actor = world.spawn_actor(unreal.StaticMeshActor, transform=unreal.Transform(location=unreal.Vector(0, 0, 0)), spawn_collision_handling_method=unreal.SpawnActorCollisionHandlingMethod.ALWAYS_SPAWN)
            actor.static_mesh_component.set_static_mesh(selected_asset)
            current_level.add_actor(actor)
            print(f"Agregado {selected_asset.get_name()} al nivel actual con colisión forzada (ALWAYS_SPAWN).")
    else:
        print("No hay nivel actual o no hay activos seleccionados en el Content Browser.")
