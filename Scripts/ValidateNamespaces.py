import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

namespaceDeclaration = "namespace TGL"
namespaceUsage = "using namespace TGL"

ignoredDirs = [
    "../Engine/Source/Internal/Asserts",
    "../Engine/Source/Internal/Macros"
]

ignoredFiles = {
    "../Engine/Source/Core/DataTypes.h"
}

ignoredDirs = [os.path.normpath(path) for path in ignoredDirs]

ignoredFiles = [os.path.normpath(path) for path in ignoredFiles]

errors : list[str] = []

for root, _, files in os.walk("../Engine/Source/"):
    if os.path.normpath(root) in ignoredDirs:
        continue
    for file in files:
        path = os.path.normpath(os.path.join(root, file))
        if path in ignoredFiles:
            continue
        with open(path, "r") as f:
            if file.endswith((".h", ".hpp")):
                if namespaceDeclaration not in f.read():
                    errors.append(f"Namespace not declared in \"{path[3:]}\"")
            elif file.endswith(".cpp"):
                if namespaceUsage not in f.read():
                    errors.append(f"Namespace not used in \"{path[3:]}\"")

if len(errors) > 0:
    print("The following errors were found:")
    for error in errors:
        print(f" - {error}")
else:
    print("The namespace was correctly declared and used")    
