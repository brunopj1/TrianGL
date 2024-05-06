import os
import re

includeRegex = re.compile(r"#include\s*\"[^\"]+\"")

os.chdir(os.path.dirname(os.path.abspath(__file__)))

errors : list[str] = []

for root, _, files in os.walk("../Engine/Source/"):
    for file in files:
        path = os.path.normpath(os.path.join(root, file))
        with open(path, "r") as f:
            invalidIncludes = includeRegex.findall(f.read())
            for include in invalidIncludes:
                errors.append(f"Denormalized include in \"{path[3:]}\": {include}")

if len(errors) > 0:
    print("The following errors were found:")
    for error in errors:
        print(f" - {error}")
else:
    print("All includes are normalized")