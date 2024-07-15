import os
import re

datatypeRegex = re.compile(r"\b(int|unsigned\s+int|unsigned|float|double)\b")

os.chdir(os.path.dirname(os.path.abspath(__file__)))

errors : list[str] = []

for root, _, files in os.walk("../Engine/Source/"):
    for file in files:
        path = os.path.normpath(os.path.join(root, file))
        with open(path, "r") as f:
            invalidDatatypes = datatypeRegex.findall(f.read())
            for datatype in invalidDatatypes:
                errors.append(f"Found '{datatype}' in \"{path[3:]}\"")

if len(errors) > 0:
    print("The following errors were found:")
    for error in errors:
        print(f" - {error}")
else:
    print("All datatypes are normalized")