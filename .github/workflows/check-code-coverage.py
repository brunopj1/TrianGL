import os
import sys
import re

# Find and open the coverage report

coverageDirs = [f for f in os.listdir() if os.path.isdir(f) and f.startswith("CoverageReport-")]

if len(coverageDirs) == 0:
    print("No coverage directories were found", file=sys.stderr)
    sys.exit(1)

content = open(coverageDirs[0] + "/index.html").read()

# Check if the coverage failed

pieGraphs = re.findall(r"new RGraph\.Pie\(", content)

if len(pieGraphs) != 2:
    print("The coverage failed to find the source code", file=sys.stderr)
    sys.exit(1)

# Find the coverage percentage

coverage = 0

coverageRes = re.search(r"\.set\('labels', \['Cover (\d+)%", content)

if coverageRes is not None:
    coverage = int(coverageRes.group(1))

# Ensure the coverage is above the threshold

print(f"The current coverage is {coverage}%")

threshold = 90

if coverage < threshold:
    print(f"The coverage is below the threshold of {threshold}%", file=sys.stderr)
    sys.exit(1)
else:
    print(f"The coverage is above the threshold of {threshold}%")
    sys.exit(0)