import os
import csv

# Ruta del directorio donde se encuentran los archivos .udatasmith
DSFolder = r'C:\Users\juanm\OneDrive\Projects\XL\01 - Model\2024004_WCC_BC_STAGING180823_V12\XL_Exported'
UEFolder = r'C:\Users\juanm\Documents\GitHub\XL_Template\Content\Python'

# Define la función para crear un archivo CSV con los nombres de archivos .udatasmith
def generate_csv(DSFolder, UEFolder):
    # Convierte la ruta del directorio a una ruta absoluta
    directory_path = os.path.abspath(DSFolder)
    csv_file_path = os.path.join(UEFolder, 'UEfilenames.csv')
    
    # Encuentra todos los archivos .udatasmith y almacena los nombres sin la extensión
    file_names = [os.path.splitext(f)[0] for f in os.listdir(directory_path) if f.endswith('.udatasmith')]
    
    # Escribe los nombres de archivo en un archivo CSV
    with open(csv_file_path, 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        # Escribe el encabezado personalizado en el CSV
        writer.writerow(['---', 'Filename'])
        # Escribe los nombres de archivo con un índice
        for index, name in enumerate(file_names, start=1):
            writer.writerow([f'{index:02}', name])
    
    print(f"CSV file created at: {csv_file_path}")


# Llama a la función
generate_csv(DSFolder)