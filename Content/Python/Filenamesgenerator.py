import os
import csv

# Ruta del directorio donde se encuentran los archivos .udatasmith
ds_folder = r'C:\Users\juanm\XL Consulting AU pty Ltd\02 - FY24 PROJECTS - Documents\2024031 - CrestLink Business Pk (Hindmarsh QLD)\03 - 3D & 4D\3D\XL_Exported'
py_folder = r'C:\Users\juanm\Documents\GitHub\XL_Template\Content\Python'

# Define la función para crear un archivo CSV con los nombres de archivos .udatasmith
def generate_csv(ds_folder, py_folder):
    # Encuentra todos los archivos .udatasmith y almacena los nombres sin la extensión
    file_names = [os.path.splitext(f)[0] for f in os.listdir(ds_folder) if f.endswith('.udatasmith')]
    
    # Ruta completa al archivo CSV dentro de la carpeta del proyecto Unreal
    csv_file_path = os.path.join(py_folder, 'UEfilenames.csv')
    
    # Escribe los nombres de archivo en un archivo CSV
    with open(csv_file_path, 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file, quoting=csv.QUOTE_ALL)  # Asegúrate de que todas las entradas estén entre comillas
        writer.writerow(['---', 'Filename'])  # Escribe el encabezado personalizado
        for index, name in enumerate(file_names, start=1):
            writer.writerow([f'{index:02}', name])  # Escribe los nombres con índice

    print(f"CSV file created at: {csv_file_path}")

# Llama a la función
generate_csv(ds_folder, py_folder)
