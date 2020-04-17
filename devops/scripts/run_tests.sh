#!/bin/bash
# PURPOSE - Execute all of the individual test scrips
# USAGE: run_tests.sh
# EXAMPLE: run_tests.sh
# NOTES:
#   Executes in the following order:
#       run_popen.sh; run_system.sh run_libpython.sh


# Purpose - Print an octothorp a certain number of times
print_line()
{
    # LOCAL VARIABLES
    LINE_LEN=$1
    LINE_STR=""
    LINE_CHAR="#"

    # INPUT VALIDATION
    if [ ${#LINE_LEN} -gt 0 ]
    then
        for (( i=0; i<($LINE_LEN+4); i++ ))
        do
            LINE_STR+="$LINE_CHAR"
        done
        echo $LINE_STR
    fi
}


# Purpose - Print a message wrapped in a banner verically
#   bookended by blank lines
print_banner()
{
    # LOCAL VARIABLES
    LINE_CHAR="#"

    # INPUT VALIDATION
    if [ ${#1} -gt 0 ]
    then
        BANNER_WIDTH=${#1}
        echo ""
        print_line $BANNER_WIDTH
        echo $LINE_CHAR $1 $LINE_CHAR
        print_line $BANNER_WIDTH
        echo ""
    fi
}


# CHANGE DIRECTORY
cd "$(dirname "$0")"  # Change directory with respect to this script

# popen
print_banner "POPEN"
./run_popen.sh

# system
print_banner "SYSTEM"
./run_system.sh

# Embedded Python3
print_banner "PYTHON'S C API"
./run_libpython.sh

# DONE
echo ""
