import os

# Modify the working directory to the folder containing the script
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Execute the coverage report script
os.system("OpenCppCoverage --cover_children --sources=Engine\\Source Bin\\Testing\\Win64\\Tests\\Tests.exe")

# Find the coverage report folder
directories = [d for d in os.listdir() if os.path.isdir(d) and d.startswith("CoverageReport")]
directories.sort()

# Open the coverage report
os.system(f"start {directories[-1]}/index.html")