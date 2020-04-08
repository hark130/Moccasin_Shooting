def prepare_file_output(filename, input_data):
    '''
        PURPOSE - Standardize the output
        PARAMS
            filename - The name of the file that invoked this module.  Must be a non-empty string.
            input_data - Data read from an input file.  Can be blank.  Must be a string
        RETURN - A newline-delimited string with out_file data to write
    '''
    # LOCAL VARIABLES
    out_data = ''

    # INPUT VALIDATION
    # filename
    if not isinstance(filename, str):
        raise TypeError('filename must be a string')
    elif not filename:
        raise ValueError('filename may not be empty')
    # input_data
    if not isinstance(input_data, str):
        raise TypeError('input_data must be a string')

    # PREPARE STRING
    out_data += '\n'
    out_data += f'INVOKING FILE: {filename}\n'  # Filename
    out_data += f'THIS FILE: {__file__}\n'  # Filename
    out_data += f'INPUT DATA:\n\t{input_data}'
    out_data += '\n'

    # DONE
    return out_data
