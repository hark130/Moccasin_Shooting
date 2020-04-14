#ifndef __MOSH_COMMAND_CAT__
#define __MOSH_COMMAND_CAT__

#define MCC_SUCCESS 0
#define MCC_INVALID_INPUT 1
#define MCC_FAILURE 2


/*
 * PURPOSE - Concatenate arguments into a single heap-allocated buffer
 * PARAMETERS
 *  arg_count - Number of items in argv
 *  arg_values - Array of character array pointers holding each argument value
 *  start_arg - Argument value to start concatenating (0 or above)
 *  stop_arg - Argument value to stop concatenating (0 through arg_count)
 * RETURNS
 *  On succes, a pointer to a heap-allocated buffer holding the concatenated argument
 *      values starting at argument start_arg and ending at stop_arg.
 *  On failure, NULL.  However, err_num will be assigned one of the following values:
 *      MCC_INVALID_INPUT - Invalid arg_count value, NULL pointer, invalid arg range, etc
 *      MCC_FAILURE - If any function calls fail past validation
 * NOTES
 *  It is the responsibility of the caller to free any valid memory addresses returned
 *  The argument count may start counting at 1 but the start_arg starts counting at 0
 *  The argument values will be separated by spaces within the returned buffer
 *  The value found at the err_num memory address will always be set to MCC_SUCCESS prior
 *      to execution
 */
char *concatenate_arguments(int arg_count, char** arg_values,
                            int start_arg, int stop_arg, int *err_num);


#endif  // __MOSH_COMMAND_CAT__
