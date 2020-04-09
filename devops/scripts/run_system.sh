#!/bin/bash
# PURPOSE - Execute the system.bin binary against all Python examples
# USAGE: run_system.sh
# EXAMPLE: run_system.sh
# NOTES:
#   Executes in the following order:
#       make system; <executes python_script0{1-6}>; <Checks output>
#   Python examples are hard-coded because python example 6 doesn't follow convention
#   Greps the output text file for references to:
#       - python_script0?.py
#       - python_script0?_in.txt file contents

SUCCESS_PREFIX="Success:"  # Use this when the test results are favorable
FAILURE_PREFIX="FAILURE!"  # Use this when some aspect of the shell script errors

# CHANGE DIRECTORY
cd "$(dirname "$0")"  # Change directory with respect to this script
cd ../..  # Change directory to the project's top level

# BUILD
make --quiet system > /dev/null 2>&1
if [ $? -ne 0 ]
then
    echo -e "\n"$FAILURE_PREFIX "Makefile recipe has failed" >&2
    echo "Replicate these results with the following command:" >&2
    echo -e "make system\n" >&2
    exit 1
fi 
