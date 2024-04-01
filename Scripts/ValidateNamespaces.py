import os
import re

os.chdir(os.path.dirname(os.path.abspath(__file__)))

namespaceDeclarationRegex = re.compile(r"namespace TGL")
namespaceUsageRegex = re.compile(r"using namespace TGL")

ignoredDirs = [
    "../Engine/Source/Util/Macros"
]

ignoredDirs = [os.path.normpath(path) for path in ignoredDirs]

errors : list[str] = []

for root, _, files in os.walk("../Engine/Source/"):
    if os.path.normpath(root) in ignoredDirs:
        continue
    for file in files:
        path = (os.path.join(root, file))
        with open(path, "r") as f:   
            if file.endswith((".h", ".hpp")):
                res = namespaceDeclarationRegex.search(f.read())
                if res is None:
                    errors.append(f"Namespace not declared in \"{path[3:]}\"")
            elif file.endswith(".cpp"):
                res = namespaceUsageRegex.search(f.read())
                if res is None:
                    errors.append(f"Namespace not used in \"{path[3:]}\"")

if len(errors) > 0:
    print("The following errors were found:")
    for error in errors:
        print(f" - {error}")
else:
    print("The namespace was correctly declared and used")    
