#!/bin/bash
# Run all six python examples

# VALIDATION
if [[ $(pwd) != *Moccasin_Shooting ]]
then
	echo -e "\nERROR: Execute this script at the project's top-level"
    EXIT 1
fi

# CLEAN UP
# Egg
rm -f dist/*.egg > /dev/null 2>&1

# Out Files
rm -f *_out.txt > /dev/null 2>&1

# EXECUTION
# 1 - Basic Functionality
python3 src/python/python_script01.py -c src/python/test_files/python_script01_in.txt
cat python_script01_out.txt

# 2 - Basic Function
python3 src/python/python_script02.py -c src/python/test_files/python_script02_in.txt
cat python_script02_out.txt

# 3 - Module Function
python3 src/python/python_script03.py -c src/python/test_files/python_script03_in.txt
cat python_script03_out.txt

# 4 - Package Function
python3 src/python/python_script04.py -c src/python/test_files/python_script04_in.txt
cat python_script04_out.txt

# 5 - Package Execution
python3 src/python/python_package/ -c src/python/test_files/python_script05_in.txt
cat python_script05_out.txt

# 6 - Egg Execution
python3 src/python/setup_python_script06.py bdist_egg --dist-dir=$(pwd)/dist --bdist-dir=$(pwd)/build > /dev/null 2>&1
python3 dist/python_script06-0.1-py3.6.egg -c src/python/test_files/python_script06_in.txt
cat python_script06_out.txt
