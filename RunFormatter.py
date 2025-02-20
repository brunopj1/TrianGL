import os
import re
import subprocess
from functools import cmp_to_key

# Modify the working directory to the folder containing the script
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Config

directories = ["Engine", "Games", "Playground", "Tests"]
extensions = ("cpp", "hpp", "h")

# Pre-compiling regex

addTargetRegex = re.compile(r"add_(?:executable|library)\s*\(([^\)]*)\)")
targetSourcesRegex = re.compile(r"target_sources\s*\(([^\)]*)\)")
pathSplitRegex = re.compile(r'/|\\+')

# Sorting functions

def sort_func(s1 : str, s2 : str):
    
    comps1 = pathSplitRegex.split(s1)
    len1 = len(comps1)

    comps2 = pathSplitRegex.split(s2)
    len2 = len(comps2)

    for i in range(min(len1, len2) - 1):
        if comps1[i] < comps2[i]:
            return -1
        if comps1[i] > comps2[i]:
            return 1
        
    if len1 != len2:
        return len2 - len1
    
    i = min(len1, len2) - 1

    if comps1[i] < comps2[i]:
        return -1
    if comps1[i] > comps2[i]:
        return 1
    else:
        return 0

# Formatting functions

def formatCppFile(path : str):
    subprocess.run(["clang-format", "-i", path], check=True)

def formatCmakeFile(path : str):
    with open(path, "r") as file:
        content = file.read()
    
    # Format the 'add_executable' / 'add_library' statement

    res = addTargetRegex.search(content)
    if res is None:
        return

    files : list[str] = []
    isLibrary = res.group(0).startswith("add_library")

    components = res.group(1).split()
    files.extend(components[2 if isLibrary else 1:])

    addTargetStatement = res.group(0).split(components[0])[0]
    addTargetStatement += components[0]
    addTargetStatement += (" " + components[1]) if isLibrary else ""
    addTargetStatement += ")"

    content = addTargetRegex.sub(addTargetStatement, content, 1)

    # Format the 'target_sources' statement

    res = targetSourcesRegex.search(content)
    if res is None:
        return

    components = res.group(1).split()
    files.extend(components[2:])

    for idx, file in enumerate(files):
        if not file.startswith("${CMAKE_CURRENT_SOURCE_DIR}/"):
            files[idx] = "${CMAKE_CURRENT_SOURCE_DIR}/" + file

    files = list(set(files))

    targetSourcesStatement = "target_sources("
    targetSourcesStatement += components[0] + " " + components[1] + "\n"

    for file in sorted(files, key=cmp_to_key(sort_func)):
        targetSourcesStatement += " " * 8 + file + "\n"
    targetSourcesStatement += ")"

    content = targetSourcesRegex.sub(targetSourcesStatement, content, 1)

    # Update the file
    with open(path, "w") as file:
        content = file.write(content)

# Run formatting

if __name__ == "__main__":
    for dir in directories:
        for root, dirs, files in os.walk(dir):
            for file in files:
                fullpath = os.path.join(root, file)
                if file == "CMakeLists.txt":
                    print(f"Formatting file: {fullpath}")
                    formatCmakeFile(fullpath)
                elif file.endswith(extensions):
                    print(f"Formatting file: {fullpath}")
                    formatCppFile(fullpath)
