import os

# Modify the working directory to the folder containing the script
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Execute the coverage report script
os.system("OpenCppCoverage --cover_children --sources=Engine\\Source Bin\\Debug\\Win64\\Tests\\Tests.exe")