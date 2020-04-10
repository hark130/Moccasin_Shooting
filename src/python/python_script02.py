"""
    PURPOSE - The most basic of function-based functionality
    DETAILS - Functionality:
        - Takes a parameter
        - Prints to stdout
        - Prints to stderr
        - Reads the filename from the parameter
        - Reads the filename's contents
        - Writes to an output file
"""

from argparse import ArgumentParser
import os
import sys


class ParseArgument(ArgumentParser):

    def parse_error(self, message):
        os.stderr.write("Error:  %s\n" % message)
        self.print_help()
        exit(2)


def parse_arguments():
    '''
        Input - None
        Output - Command line argument list from ParseArgument object
        Note - Lifted shamelessly from:
            https://github.com/hark130/XCOM2_Randomizer/blob/master/xrando.py
    '''
    # Parser object
    parser = ParseArgument()

    # Command line arguments
    parser.add_argument("-c", "--config", required=True, help="Input configuration file")

    # List of arguments from the command line
    args = parser.parse_args()

    return args


def prepare_file_output(input_data):
    '''
        PURPOSE - Standardize the output
        PARAMS
            input_data - Data read from an input file.  Can be blank.  Must be a string
        RETURN - A newline-delimited string with out_file data to write
    '''
    # LOCAL VARIABLES
    out_data = ''

    # INPUT VALIDATION
    if not isinstance(input_data, str):
        raise TypeError('input_data must be a string')

    # PREPARE STRING
    out_data += '\n'
    out_data += f'THIS FILE: {__file__}\n'  # Filename
    out_data += f'INPUT DATA:\n\t{input_data}'
    out_data += '\n'

    # DONE
    return out_data


def print_output(file_name):
    '''
        PURPOSE - Standardize the printed output
        PARAMS
            file_name - File name to print as a string.  May not be empty.
    '''
    # INPUT VALIDATION
    if not isinstance(file_name, str):
        raise TypeError('file_name must be a string')
    elif not file_name:
        raise ValueError('file_name may not be empty')

    # PRINT
    print('\n')
    print(f'This is {file_name} stdout', file=sys.stdout)
    print(f'This is {file_name} stderr', file=sys.stderr)
    print('\n')


def main():
    # LOCAL VARIABLES
    (file_path, file_name) = os.path.split(__file__)
    output_filename = file_name.replace('.py', '_out.txt')
    parsed_args = parse_arguments()
    out_data = ''  # Create and store the output file contents here

    # WORK
    # 1. Print Output
    print_output(file_name)

    # 2. Read "Config" File
    with open(parsed_args.config, 'r') as in_file:
        input_data = in_file.read()
        out_data = prepare_file_output(input_data)

        # 3. Write Output File
        with open(output_filename, 'w') as out_file:
            out_file.write(out_data)


if __name__ == "__main__":
    main()
