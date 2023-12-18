import os
import csv








ds_folder = r'C:\Users\JuanMaldini\XL Consulting AU pty Ltd\02 - FY24 PROJECTS - Documents\2024038 - Banksmeadow Mult. Ind. Dev. (Hindmarsh)\03 - 3D & 4D\3D\XL_Exported'
py_folder = r'C:\Users\JuanMaldini\Documents\GitHub\XL_Template\Content\Python'








# Define la función para crear un archivo CSV con los nombres de archivos .udatasmith
def generate_csv(ds_folder, py_folder):
    # Encuentra todos los archivos .udatasmith y almacena los nombres sin la extensión
    file_names = [os.path.splitext(f)[0] for f in os.listdir(ds_folder) if f.endswith('.udatasmith')]
    
    # Ruta completa al archivo CSV dentro de la carpeta del proyecto Unreal
    csv_file_path = os.path.join(py_folder, 'UEfilenames.csv')
    
    # Escribe los nombres de archivo en un archivo CSV
    with open(csv_file_path, 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file, quoting=csv.QUOTE_ALL)
        writer.writerow(['---', 'Filename'])
        for index, name in enumerate(file_names, start=1):
            writer.writerow([f"{index:02}", name])

    print(f"CSV file created at: {csv_file_path}")

# Ejemplo de cómo podrías llamar a esta función directamente con rutas codificadas
generate_csv(ds_folder, py_folder)
