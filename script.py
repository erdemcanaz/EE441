from pathlib import Path
import os
import sys

EE441_FOLDER_PATH = Path(__file__).parent

SUB_FOLDER_NAME = sys.argv[1]
SUB_FOLDER_PATH = EE441_FOLDER_PATH / SUB_FOLDER_NAME

EXE_NAME = SUB_FOLDER_NAME.replace(" ", "\ ")+".exe"

if not os.path.exists(SUB_FOLDER_PATH):
    #Be sure that such folder path exists
    raise Exception(f"The path '{SUB_FOLDER_PATH}' does not exist")

#change directory to SUB_FOLDER_PATH
os.chdir(SUB_FOLDER_PATH)

#==============================================================================

def delete_all_o_and_exe_files():
    #delete all object files which has .o extension and all exe files with .exe extension
    all_file_names_in_sub_folder = os.listdir()

    for file_name in all_file_names_in_sub_folder:
        if file_name.endswith(".o") or file_name.endswith(".exe"):
            os.remove(SUB_FOLDER_PATH / file_name)

def compile_all_cpp_files():
    #compile all cpp files
    all_file_names_in_sub_folder = os.listdir()
    for file_name in all_file_names_in_sub_folder:
        if file_name.endswith(".cpp"):
            os.system(f"g++ -c {file_name}")

def link_all_o_files_and_create_exe():
    #link objects and create executable
    all_file_names_in_sub_folder = os.listdir()
    object_file_names = []
    for file_name in all_file_names_in_sub_folder:
        if file_name.endswith(".o"):
            object_file_names.append(file_name)

    if len(object_file_names) == 0:
        raise Exception("There is no cpp file in the folder. Thus there is no object file is compiled. Meaning that there is no executable file to be created")

    EXE_NAME = SUB_FOLDER_NAME.replace(" ", "\ ")+".exe"
    object_file_names_str = " ".join(object_file_names)
    os.system(f"g++ -o {EXE_NAME} {object_file_names_str}")


if __name__ == "__main__":
    
    #delete all object files and exe files
    if("--d" in sys.argv or "--full" in sys.argv):
        delete_all_o_and_exe_files()
    
    #compile all cpp files
    if("--c" in sys.argv or "--full" in sys.argv):
        compile_all_cpp_files()
    
    #link all o files and create exe
    if("--l" in sys.argv or "--full" in sys.argv):
        link_all_o_files_and_create_exe()
    
    #run the exe file
    if("--r" in sys.argv or "--full" in sys.argv):
        os.system(f"./{EXE_NAME}")

    #delete all object files and exe files
    if("--full" in sys.argv and "--clean" in sys.argv):
        delete_all_o_and_exe_files()



