import os
import shutil
import subprocess

def delete_vs_files(directory : str):

    if not os.path.exists(directory):
        return

    for file in os.listdir(directory):
        if file.endswith((".vcxproj", ".vcxproj.user", ".vcxproj.filters")):
            os.remove(os.path.join(directory, file))

def delete_vs_files_in_parent(directory : str):

    if not os.path.exists(directory):
        return

    for child in os.listdir(directory):
        child_path = os.path.join(directory, child)
        if os.path.isdir(child_path):
            delete_vs_files(child_path)

def delete_coverage_files():

    if os.path.exists("LastCoverageResults.log"):
        os.remove("LastCoverageResults.log")

    for file in os.listdir():
        if os.path.isdir(file) and file.startswith("CoverageReport-"):
            shutil.rmtree(file)

# Modify the working directory to the folder containing the script
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Delete the Build folders
shutil.rmtree("Bin", ignore_errors=True)
shutil.rmtree("Obj", ignore_errors=True)

# Delete the Visual Studio files
delete_vs_files("Engine")
delete_vs_files_in_parent("Libs")
delete_vs_files_in_parent("Playground")
delete_vs_files_in_parent("Games")

# Delete the Visual Studio solution
if os.path.exists("TrianGL.sln"):
    os.remove("TrianGL.sln")

# Delete the coverage files
delete_coverage_files()

# Init the git submodules
subprocess.run(["git", "submodule", "update", "--init", "--recursive"], check=True)

# Build and open the Visual Studio solution
os.system("Premake\\premake5.exe vs2022")
os.startfile("TrianGL.sln")