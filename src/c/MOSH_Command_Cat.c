// Standard Includes
#include <stdbool.h>
#include <string.h>
// Local Includes
#include "MOSH_Command_Cat.h"

#define MCC_ERROR(header, funcName, msg) do { fprintf(stderr, "<<<ERROR>>> - %s - %s() - %s!\n", #header, #funcName, #msg); } while (0);
#define MCC_ERRNO(header, funcName, errorNum) if (errorNum) { fprintf(stderr, "<<<ERROR>>> - %s - %s() returned errno:%s\n", #header, #funcName, strerror(errorNum)); }
#define MCC_NAME "MOSH_Command_Cat"


/*
 *  PURPOSE - Validates the input provided to concatenate_arguments()
 *  PARAMETERS - See concatenate_arguments() function comment block
 *  RETURNS
 *   On succes, MCC_SUCCESS
 *   On failure, MCC_INVALID_INPUT
 */
int validate_input(int arg_count, char **arg_values, int start_arg, int stop_arg);


/*
 *  PURPOSE - Determine the total size, in bytes, necessary to store indicated arguments
 *  PARAMETERS - See concatenate_arguments() function comment block
 *  NOTES
 *      - This function does not validate its input
 *  RETURNS - Total size necessary, including spaces between argument values and room for a
 *      nul terminator
 */
size_t deterine_necessary_size(char **arg_values, int start_arg, int stop_arg);


/*
 *  PURPOSE - Copy the argument values, starting at arg_values[start_arg] and ending at
 *      arg_values[stop_arg] (inclusive), into the buffer located at dest.
 *  PARAMETERS
 *      dest - Buffer with enough space to hold all the argument values between start_arg and
 *          stop_arg (inclusive) with spaces between argument values and a trailing nul-terminator
 *      arg_values - See concatenate_arguments() function comment block
 *      start_arg - See concatenate_arguments() function comment block
 *      stop_arg - See concatenate_arguments() function comment block
 *  NOTES
 *      - Only dest is validated
 *      - This function does not allocate memory
 *      - It goes without saying that it's the responsibility of the caller to ensure there's
 *          adequate memory allocated to the buffer found at dest's pointer
 *  RETURNS
 *   On succes, MCC_SUCCESS
 *   On failure, MCC_INVALID_INPUT or MCC_FAILURE (see: MOSH_Command_Cat.h)
 */
int copy_in_arg_values(char *dest, char **arg_values, int start_arg, int stop_arg);


char *concatenate_arguments(int arg_count, char** arg_values,
                            int start_arg, int stop_arg, int *err_num)
{
    // LOCAL VARIABLES
    char *concat_params = NULL;   // Return value
    bool success = true;          // Controls the flow of the entire function
    size_t buff_size = 0;         // Overall size of the buffer
    int temp_errno = 0;           // Store errno here

    // INPUT VALIDATION
    // err_num
    if (err_num)
    {
        *err_num = validate_input(arg_count, arg_values, start_arg, stop_arg);
    }
    else
    {
        return concat_params;
    }

    // CONCATENATE PARAMETERS
    // Determine Buffer Size
    if (MCC_SUCCESS == *err_num)
    {
        buff_size = deterine_necessary_size(arg_values, start_arg, stop_arg);

        if (buff_size < 2)
        {
            *err_num = MCC_FAILURE;
            MCC_ERROR(MCC_NAME, concatenate_arguments, deterine_necessary_size invalid result);
        }
    }

    // Allocate Memory
    if (MCC_SUCCESS == *err_num)
    {
        concat_params = calloc(buff_size, 1);

        if (!concat_params)
        {
            temp_errno = errno;
            *err_num = MCC_FAILURE;
            MCC_ERROR(MCC_NAME, concatenate_arguments, calloc failed);
            MCC_ERRNO(header, funcName, temp_errno);
        }
    }

    // Copy In Parameters
    if (MCC_SUCCESS == *err_num)
    {
        *err_num = copy_in_arg_values(concat_params, arg_values, start_arg, stop_arg);
    }

    // CLEANUP
    if (MCC_SUCCESS != *err_num && concat_params)
    {
        // Zeroize
        if (concat_params != memset(concat_params, 0x0, buff_size))
        {
            temp_errno = errno;
            MCC_ERROR(MCC_NAME, concatenate_arguments, memset failed);
            MCC_ERRNO(header, funcName, temp_errno);
        }
        // Free
        free(concat_params);
        // NULL
        concat_params = NULL;
    }

    // DONE
    return concat_params;
}


int validate_input(int arg_count, char **arg_values, int start_arg, int stop_arg)
{
    // LOCAL VARIABLES
    int result = MCC_SUCCESS;  // Return value
    int i = 0;                 // Iterating variable

    // VALIDATION
    // arg_count
    if (arg_count < 1)
    {
        result = MCC_INVALID_INPUT;
        MCC_ERROR(MCC_NAME, validate_input, Invalid arg_count value);
    }
    // arg_values
    else if (!arg_values)
    {
        result = MCC_INVALID_INPUT;
        MCC_ERROR(MCC_NAME, validate_input, Invalid arg_values pointer);
    }
    // start_arg
    else if (start_arg < 0 || start_arg >= arg_count)
    {
        result = MCC_INVALID_INPUT;
        MCC_ERROR(MCC_NAME, validate_input, Invalid start_arg value);
    }
    // stop_arg
    else if (stop_arg >= arg_count)
    {
        result = MCC_INVALID_INPUT;
        MCC_ERROR(MCC_NAME, validate_input, stop_arg can not exceed arg_count);
    }

    // Compare arg_count to arg_values
    if (MCC_SUCCESS == result)
    {
        for (i = 0; i < arg_count; i++)
        {
            // Verify not NULL
            if (!(*(arg_values + i)))
            {
                result = MCC_INVALID_INPUT;
                MCC_ERROR(MCC_NAME, validate_input, Invalid pointer found in arg_values array);
            }
            // Verify not empty
            else if (0 == strlen((*(arg_values + i))))
            {
                result = MCC_INVALID_INPUT;
                MCC_ERROR(MCC_NAME, validate_input, arg_values array contains an empty string);
            }
        }
        // Verify NULL
        if ((*(arg_values + i)))
        {
            result = MCC_INVALID_INPUT;
            MCC_ERROR(MCC_NAME, validate_input, The pointers in arg_values exceeds arg_count);
        }
    }

    // Compare start_arg to stop_arg
    if (MCC_SUCCESS == result)
    {
        if (start_arg > stop_arg)
        {
            result = MCC_INVALID_INPUT;
            MCC_ERROR(MCC_NAME, validate_input, start_arg can not be greater than stop_arg);
        }
    }

    // DONE
    return result;
}


size_t deterine_necessary_size(char **arg_values, int start_arg, int stop_arg)
{
    // LOCAL VARIABLES
    size_t necessary_size = 0;  // Return value
    int i = 0;                  // Iterating variable

    // DETERMINE NECESSARY SIZE
    for (i = start_arg; i <= stop_arg; i++)
    {
        necessary_size += (strlen((*(arg_values + i)) * sizeof(char)));  // Arg value length
        necessary_size += sizeof(char);  // Room for space or nul terminator
    }

    // DONE
    return necessary_size;
}


int copy_in_arg_values(char *dest, char **arg_values, int start_arg, int stop_arg)
{
    // LOCAL VARIABLES
    int result = MCC_SUCCESS;  // Return value
    int i = 0;                 // Iterating variable
    char *tmp_buff = dest;      // Temporary pointer to iterate

    // INPUT VALIDATION
    if (!dest)
    {
        result = MCC_INVALID_INPUT;
        MCC_ERROR(MCC_NAME, copy_in_arg_values, Invalid pointer found in dest parameter);
    }

    // COPY IN ARG VALUES
    if (true == result)
    {
        for (i = start_arg; i <= stop_arg; i++)
        {
            if (tmp_buff != strcpy(tmp_buff, (*(arg_values + i))))
            {
                result = MCC_FAILURE;
                MCC_ERROR(MCC_NAME, copy_in_arg_values, strcpy has failed);
                break;
            }
            else
            {
                // Advance the pointer past the string that got copied in
                tmp_buff += (strlen((*(arg_values + i))) * sizeof(char));
                // Delimit the concatenated string
                if (i < stop_arg)
                {
                    // There are more commands to copy in
                    *tmp_buff = ' ';  // Add a space
                    tmp_buff++;  // Advance to the next position
                }
                else
                {
                    *tmp_buff = '\0';  // Manually terminate the buffer... for safety
                }
            }
        }
    }

    // DONE
    return result
}
