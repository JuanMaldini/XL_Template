#Instructions

#Download and install
https://www.unrealengine.com/en-US/datasmith/plugins				Datasmith Exporter
https://dotnet.microsoft.com/es-es/download					SDK for compile project
https://developer.microsoft.com/en-US/windows/downloads/windows-sdk/		SDK for compile project
https://git-scm.com/download/win						Software for check updates
https://git-lfs.com/								Software for big Unreal projects
https://desktop.github.com/							Software for download projects
https://www.python.org/downloads/						Software for create Datasmith names

#Download the project. Code > Open with Github Desktop > Clone
https://github.com/JuanMaldini/XL_Template					Repository in cloud (project)

#Wait until finish download project

#Go to the folder inside repository > Sketchup script
Copy "XL_Export_Actual_Scene_Buttom" & "XL_Export_Actual_Scene_Buttom" to "C:\Users\USERNAME\AppData\Roaming\SketchUp\SketchUp 2022\SketchUp\Plugins"

#Create DatasmithFiles for Unreal
Open 3d model in Sketchup > Extensions > XL Export All Scenes. It will create all DatasmithScenes in same folder

#Now we have the DatasmithFiles from sketchup, lets create the names for Unreal.
"C:\PROJECT PATH\XL_Template\Content\Python" > Filenamesgenerator > Open with notepad > modify 2 paths for name creation
Modify "ds_folder" & "py_folder"

#EXAMPLE
ds_folder = r'C:\Users\USERNAME\XL Consulting AU pty Ltd\02 - FY24 PROJECTS - Documents\2024050 - GPT Apex Stage 3 (Hindmarsh QLD)\03 - 3D & 4D\3D\XL_Exported'
py_folder = r'C:\Users\USERNAME\Documents\GitHub\XL_Template\Content\Python'

Now we have setup Filenamesgenerator.py file > Open with python > It will create automaticly the naming for Unreal 

Go to the folder downloaded > Open "XL_Template.uproject" (If fail, try again, it will compile)

#Now we are inside Unreal

On bottom left > Content Browser > Content > Find "XL_Pipeline" > Right Click "Run Editor Utility Widget"

Look for the window opened and fill the paths "C:\XL_Exported" & "C:\XL_Template\Content\Python" you should see the DatasmithFile to import > Select > "Import File" > Wait > "Run Actions" 

#Procced to make render 

"XL_Pipeline" > Select Cameras

#Two ways to make render.

1)Long way without plugin.

	Content > Movie > Open "SEQ_00" > Right click under Camera Cut > "Actor To Sequencer" > "Add Currect Selection" > Right click in the timeline Camera Cut and select the camera you will render to assign for the view render.
	Click in the 5th button Movie Render Queue
	Window will appear > in settings add the preset > Unsaved Config > Select > XL_RenderPrest
	Render Local

2) Shot way > It will be with Metashoot plugin to automate to render of multiple cameras just clicking on them.
	Pressing the button of "XL_Pipeline" > Select Cameras
	Unreal Editor window > Tools > Editor Utility Widgets > Metashoot
	With selected cameras press Render