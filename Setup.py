import os
import subprocess

# Modify the working directory to the folder containing the script
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Init the git submodules
subprocess.run(["git", "submodule", "update", "--init", "--recursive"], check=True)

# Ignore any modifications on the 'mappings.h' file inside the glfw repository
subprocess.run(["git", "update-index", "--assume-unchanged", "mappings.h"], cwd="Libs/glfw/glfw/src", check=True)

# Checkout the Wiki to the main branch
subprocess.run(["git", "-C", "Wiki", "checkout", "master"], check=True)
