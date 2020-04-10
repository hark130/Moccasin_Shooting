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


# Purpose - Tests parameter 1 for length 0
# Return - 1 if empty, 0 if not
validate_input_not_empty()
{
    if [ ${#1} -gt 0 ]
    then
        return 0
    else
        return 1
    fi
}


# Purpose - Searches for a string-needle in a file-haystack
# Parameters
#   First parameter - "Needle" string
#   Second parameter - "Haystack" filename
# Notes
#   - Utilizes grep
# Return - 0 if found, 1 if not, 2 on error
find_in_file()
{
    # LOCAL VARIABLES
    PARAM_NEEDLE=$1
    PARAM_HAYSTACK=$2
    RETVAL=0

    # INPUT VALIDATION
    # echo $PARAM_HAYSTACK  # DEBUGGING
    # PARAM_NEEDLE
    validate_input_not_empty $PARAM_NEEDLE
    if [ $? -ne 0 ]
    then
        echo -e "\n"$FAILURE_PREFIX "The 'needle' parameter is invalid\n" >&2
        return 2
    fi
    # PARAM_HAYSTACK
    validate_input_not_empty $PARAM_HAYSTACK
    if [ $? -ne 0 ]
    then
        echo -e "\n"$FAILURE_PREFIX "The 'haystack' parameter is invalid\n" >&2
        return 2
    fi
    # Verify haystack exists
    test -f $PARAM_HAYSTACK
    if [ $? -ne 0 ]
    then
        echo -e "\n"$FAILURE_PREFIX "The 'haystack' "$PARAM_HAYSTACK" does not exist\n" >&2
        return 2
    fi

    # SEARCH
    grep "$PARAM_NEEDLE" $PARAM_HAYSTACK > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        return 0  # Found it
    else
        echo -e "\n"$FAILURE_PREFIX "Unable to find '"$PARAM_NEEDLE"' in" $PARAM_HAYSTACK"\n" >&2
        return 1  # Didn't find it
    fi

    # DONE(?!)
    return 2  # If you made it here, something went wrong
}


TEST_NUM=1  # Always start with the first test
PYTHON_COMMAND="python3"
SOURCE_DIR="src/python/"
DIST_DIR="dist/"
LOG_DIR="devops/logs/"
BINARY_NAME="system.bin"
BINARY_REL_NAME=$DIST_DIR$BINARY_NAME
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
EXAMPLE_ARG="-c"
INPUT_FILE_PREFIX="python_script0"
INPUT_FILE_SUFFIX="_in.txt"
INPUT_FILE_PATH=$SOURCE_DIR"test_files/"
TEMP_LOG_FILE_STDOUT="temp_log_stdout.txt"
TEMP_LOG_FILE_STDERR="temp_log_stderr.txt"
TEMP_LOG_REL_FILE_STDOUT=$LOG_DIR$TEMP_LOG_FILE_STDOUT
TEMP_LOG_REL_FILE_STDERR=$LOG_DIR$TEMP_LOG_FILE_STDERR

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

# PRE-CLEANUP
for TEMP_FILE in $TEMP_LOG_REL_FILE_STDOUT $TEMP_LOG_REL_FILE_STDERR
do
    test -f $TEMP_FILE
    if [ $? -eq 0 ]
    then
        rm -f $TEMP_FILE
        if [ $? -ne 0 ]
        then
            echo -e "\n"$FAILURE_PREFIX" failed to delete "$TEMP_FILE"\n" >&2
        fi
    fi
done

# EXECUTE
for PYTHON_FILE in $PYTHON_REL_FILE_1 $PYTHON_REL_FILE_2 $PYTHON_REL_FILE_3 $PYTHON_REL_FILE_4 $PYTHON_REL_FILE_5 $PYTHON_REL_FILE_6
do
    # SET TEMP VARIABLES
    TEMP_COMMAND=$BINARY_REL_NAME" "$PYTHON_COMMAND" "$PYTHON_FILE" "$EXAMPLE_ARG" "$INPUT_FILE_PATH$INPUT_FILE_PREFIX$TEST_NUM$INPUT_FILE_SUFFIX
    TEMP_TEST_NAME=$INPUT_FILE_PREFIX$TEST_NUM".py"
    TEMP_STDOUT_NEEDLE="This is "$TEMP_TEST_NAME" stdout"
    TEMP_STDERR_NEEDLE="This is "$TEMP_TEST_NAME" stderr"
    TEMP_OUT_TXT_FILE=$INPUT_FILE_PREFIX$TEST_NUM"_out.txt"
    TEMP_OUT_TXT_NEEDLE1=$TEMP_TEST_NAME  # e.g., python_script01.py
    TEMP_OUT_TXT_NEEDLE2=$INPUT_FILE_PREFIX$TEST_NUM"_in.txt file contents"  # e.g., python_script01_in.txt file contents
    TEMP_NUM_ERRORS=0

    # Execute the command
    # $TEMP_COMMAND
    $TEMP_COMMAND 1> $TEMP_LOG_REL_FILE_STDOUT 2> $TEMP_LOG_REL_FILE_STDERR
    if [ $? -eq 0 ]
    then
        # echo $SUCCESS_PREFIX "Found" $INPUT
        # echo $INPUT_FILE_PATH$INPUT_FILE_PREFIX$TEST_NUM$INPUT_FILE_SUFFIX
        # echo $TEMP_COMMAND
        # echo $SUCCESS_PREFIX "for" $PYTHON_FILE
        # cat $TEMP_LOG_REL_FILE_STDOUT
        # cat $TEMP_LOG_REL_FILE_STDERR

        # VALIDATION
        # 1. stdout
        find_in_file "$TEMP_STDOUT_NEEDLE" $TEMP_LOG_REL_FILE_STDOUT
        if [ $? -ne 0 ]
        then
            ((TEMP_NUM_ERRORS=TEMP_NUM_ERRORS+1))
        fi

        # 2. stderr
        find_in_file "$TEMP_STDERR_NEEDLE" $TEMP_LOG_REL_FILE_STDERR
        if [ $? -ne 0 ]
        then
            ((TEMP_NUM_ERRORS=TEMP_NUM_ERRORS+1))
        fi

        # 3. *_out.txt
        # 3.a. Verify it was created
        test -f $TEMP_OUT_TXT_FILE
        if [ $? -ne 0 ]
        then
            echo -e "\n"$FAILURE_PREFIX" Unable to locate "$TEMP_OUT_TXT_FILE"\n" >&2
            ((TEMP_NUM_ERRORS=TEMP_NUM_ERRORS+1))
        else
            # 3.b. Search for needle 1
            find_in_file "$TEMP_OUT_TXT_NEEDLE1" $TEMP_OUT_TXT_FILE
            if [ $? -ne 0 ]
            then
                ((TEMP_NUM_ERRORS=TEMP_NUM_ERRORS+1))
            fi
            # 3.c. Search for needle 2
            find_in_file "$TEMP_OUT_TXT_NEEDLE2" $TEMP_OUT_TXT_FILE
            if [ $? -ne 0 ]
            then
                ((TEMP_NUM_ERRORS=TEMP_NUM_ERRORS+1))
            fi
        fi

        # 4. Summary
        if [ $TEMP_NUM_ERRORS -eq 0 ]
        then
            echo "[X]" $TEMP_TEST_NAME "passed"
        else
            echo "[ ]" $TEMP_TEST_NAME "FAILED!"
        fi
    else
        echo -e "\n"$FAILURE_PREFIX "Python failed" >&2
        echo "Replicate the error with the following command:" >&2
        echo -e $TEMP_COMMAND"\n" >&2
    fi
    ((TEST_NUM=TEST_NUM+1))
done

# DONE
echo ""
