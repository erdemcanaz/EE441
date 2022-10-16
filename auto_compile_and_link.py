from pathlib import Path
import os

#Be sure that this file is located under the folder EE441
EE441_FOLDER_PATH = Path(__file__).parent
#TODO: get this path as input from the user
SUB_FOLDER_NAME = "header file example"



SUB_FOLDER_PATH = EE441_FOLDER_PATH / SUB_FOLDER_NAME
if not os.path.exists(SUB_FOLDER_PATH):
    #Be sure that such folder path exists
    raise Exception(f"The path '{SUB_FOLDER_PATH}' does not exist")

#change directory to SUB_FOLDER_PATH
os.chdir(SUB_FOLDER_PATH)

#get all file names in SUB_FOLDER_PATH
all_file_names_in_sub_folder = os.listdir()

#delete all object files which has .o extension and all exe files with .exe extension
for file_name in all_file_names_in_sub_folder:
    if file_name.endswith(".o") or file_name.endswith(".exe"):
        os.remove(SUB_FOLDER_PATH / file_name)

#compile all cpp files
for file_name in all_file_names_in_sub_folder:
    if file_name.endswith(".cpp"):
        os.system(f"g++ -c {file_name}")

#get all file names in SUB_FOLDER_PATH
all_file_names_in_sub_folder = os.listdir()

#link objects and create executable
object_file_names = []
for file_name in all_file_names_in_sub_folder:
    if file_name.endswith(".o"):
        object_file_names.append(file_name)

if len(object_file_names) == 0:
    raise Exception("There is no object file in the folder")

else:
    EXE_NAME = SUB_FOLDER_NAME.replace(" ", "\ ")
    object_file_names_str = " ".join(object_file_names)
    os.system(f"g++ -o {EXE_NAME}.exe {object_file_names_str}")









# print(os.getcwd())

#os.system("mkdir folder")

# os.system("echo Hello from the other side!")
# os.system("ls -a")
# os.system("cd ..")

# p = pathlib.Path(__file__).parent
# print(p)
#os.system(f"cd {os.getcwd()}")

#os.system(f"cd {__file__}")
