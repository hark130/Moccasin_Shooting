#!/bin/bash
# PURPOSE - Execute the system.bin binary against all Python examples
# USAGE: run_system.sh
# EXAMPLE: run_system.sh
# NOTES:
#   Executes in the following order:
#       make system; <executes python_script0{1-6}>; <Checks output>
#   Python examples are hard-coded because python example 5 and 6 don't follow convention
#   Greps the output text file for references to:
#       - python_script0?.py
#       - python_script0?_in.txt file contents

SUCCESS_PREFIX="Success:"  # Use this when the test results are favorable
FAILURE_PREFIX="FAILURE!"  # Use this when some aspect of the shell script errors

SOURCE_DIR="src/python/"
DIST_DIR="dist/"
PYTHON_FILE_1="python_script01.py"
PYTHON_FILE_2="python_script02.py"
PYTHON_FILE_3="python_script03.py"
PYTHON_FILE_4="python_script04.py"
PYTHON_FILE_5="python_package/"
PYTHON_FILE_6="python_script06-0.1-py3.6.egg"
PYTHON_REL_FILE_1=$SOURCE_DIR$PYTHON_FILE_1
PYTHON_REL_FILE_2=$SOURCE_DIR$PYTHON_FILE_2
PYTHON_REL_FILE_3=$SOURCE_DIR$PYTHON_FILE_3
PYTHON_REL_FILE_4=$SOURCE_DIR$PYTHON_FILE_4
PYTHON_REL_FILE_5=$SOURCE_DIR$PYTHON_FILE_5
PYTHON_REL_FILE_6=$DIST_DIR$PYTHON_FILE_6

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

# EXECUTE
for INPUT in $PYTHON_REL_FILE_1 $PYTHON_REL_FILE_2 $PYTHON_REL_FILE_3 $PYTHON_REL_FILE_4 $PYTHON_REL_FILE_5 $PYTHON_REL_FILE_6
do
    test -f $INPUT
    if [ $? -eq 0 ]
    then
        echo $SUCCESS_PREFIX "Found" $INPUT
    else
        echo $FAILURE_PREFIX "Unable to find" $INPUT
    fi
done
