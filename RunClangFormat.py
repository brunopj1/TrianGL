import os
from glob import glob

# Helper functions

def findSourceFiles(directories : list[str], extensions : list[str]) -> list[str]:

    files : list[str] = []

    for dir in directories:
        for ext in extensions:
            files += glob(f"{dir}/**/*.{ext}", recursive=True)

    files.sort()

    return files

# Modify the working directory to the folder containing the script
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Find all source files

directories = ["Engine", "Playground", "Games", "Tests"]
extensions = ["cpp", "hpp", "h"]

files = findSourceFiles(directories, extensions)

for file in files:
    print(f"Formatting: {file}")
    os.system(f"clang-format -i {file}")