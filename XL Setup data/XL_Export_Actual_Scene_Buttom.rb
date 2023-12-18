require "sketchup.rb"

# " " > "_"

# Acceder al modelo actual
modelo = Sketchup.active_model

# Acceder a las páginas (escenas) del modelo
paginas = modelo.pages

# Recorrer cada página (escena)
paginas.each do |pagina|
  # Obtener el nombre de la escena
  nombre_original = pagina.name

  # Verificar si el nombre contiene espacios
  if nombre_original.include?(" ")
    # Reemplazar los espacios por guiones bajos
    nombre_nuevo = nombre_original.gsub(" ", "_")

    # Actualizar el nombre de la escena
    pagina.name = nombre_nuevo

    # Opcional: imprimir los nombres para verificar
    puts "Nombre cambiado: #{nombre_original} -> #{nombre_nuevo}"
  end
end

puts "Revisión de nombres de escenas completada."

#Export

model = Sketchup.active_model
  folder_path = File.dirname(model.path)

# Obtén la lista de todas las páginas en el modelo
pages = Sketchup.active_model.pages

# Directorio de destino para los archivos .udatasmith
target_dir = folder_path + "/XL_Exported"

#add in menu
UI.menu("Extensions").add_item("XL Export Actual Scene"){

# Verifica si hay al menos una página en el modelo
if pages.length > 0

    # Activa la página actual
    page = Sketchup.active_model.pages.selected_page

    # Nombre para el archivo .udatasmith (usamos el nombre de la página)
    export_name = page.name

    # Reemplaza los caracteres no permitidos en nombres de archivo
    export_name = export_name.gsub(/[\\\/:*?"<>|]/, '_')

    # Exporta la página actual como .udatasmith
    EpicGames::Datasmith.export export_name, target_dir

    # Muestra un mensaje en la consola
    puts "Exportando '#{page.name}' como '#{export_name}.udatasmith' a '#{target_dir}'"
else
    puts "No se encontraron páginas en el modelo."
end
}