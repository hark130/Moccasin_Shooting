// Standard Includes
#include <errno.h>      // errno
#include <stdlib.h>     // MACROS
// Third Party Includes
#include <python3.6/Python.h>
// Local Includes
#include "MOSH_Command_Cat.h"


void free_wargv(int argc, wchar_t **wargv)
{
    // LOCAL VARIABLES
    int i = 0;                  // Iterating variable
    wchar_t *temp_warg = NULL;  // Temp index of wargv

    // INPUT VALIDATION
    if (wargv && argc > 0)
    {
        // Free Contents
        for (i = 0; i < argc; i++)
        {
            temp_warg = (*(wargv + i));
            if (temp_warg)
            {
                // Free
                free(temp_warg);
            }
            else
            {
                break;  // Hit a NULL value
            }
        }
        // ZEROIZE
        memset(wargv, 0x0, sizeof(wchar_t *) * argc);
    }

    // Free Array Pointer
    if (wargv)
    {
        free(wargv);
    }

    // DONE
    return;
}


wchar_t **convert_argv_to_wargv(int argc, char **argv)
{
    // LOCAL VARIABLES
    wchar_t **changed_argv = NULL;  // Return value
    int status = EXIT_SUCCESS;      // Flow control variable
    int err_num = 0;                // Store errno here
    int i = 0;                      // Iterating variable
    size_t temp_strlen = 0;         // Temp variable
    size_t temp_converted = 0;      // Temp number of wide chars converted

    // INPUT VALIDATION
    if (argc > 0 && argv)
    {
        status = EXIT_SUCCESS;
    }
    else
    {
        status = EXIT_FAILURE;
    }

    // CONVERT
    // Allocate
    if (EXIT_SUCCESS == status)
    {  
        changed_argv = calloc(argc + 1, sizeof(wchar_t *));

        if (!changed_argv)
        {
            err_num = errno;
            status = EXIT_FAILURE;
            MCC_ERROR(main_libpython, convert_argv_to_wargv, calloc appears to have failed to allocate the entire array);
            MCC_ERRNO(main_libpython, calloc, err_num);
        }
    }

    // Loop
    if (EXIT_SUCCESS == status)
    {
        for (i = 0; i < argc; i++)
        {
            // Calculate strlen
            temp_strlen = strlen((*(argv + i)));

            if (temp_strlen < 1)
            {
                err_num = errno;
                status = EXIT_FAILURE;
                MCC_ERROR(main_libpython, convert_argv_to_wargv, strlen appears to have failed);
                MCC_ERRNO(main_libpython, strlen, err_num);
                break;
            }

            // Allocate
            (*(changed_argv + i)) = calloc(temp_strlen + 1, sizeof(wchar_t));

            if (!(*(changed_argv + i)))
            {
                err_num = errno;
                status = EXIT_FAILURE;
                MCC_ERROR(main_libpython, convert_argv_to_wargv, calloc appears to have failed);
                MCC_ERRNO(main_libpython, calloc, err_num);
                break;
            }

            // Convert
            temp_converted = mbstowcs((*(changed_argv + i)), (*(argv + i)), temp_strlen + 1);

            if (temp_converted != temp_strlen)
            {
                err_num = errno;
                status = EXIT_FAILURE;
                MCC_ERROR(main_libpython, convert_argv_to_wargv, mbstowcs appears to have failed);
                MCC_ERRNO(main_libpython, mbstowcs, err_num);
                break;
            }
        }
    }

    // CLEAN UP
    if (EXIT_SUCCESS != status)
    {
        // Free
        free_wargv(argc, changed_argv);
        // NULL
        changed_argv = NULL;
    }

    // DONE
    return changed_argv;
}


int main(int argc, char **argv)
{
    // LOCAL VARIABLES
    int status = EXIT_SUCCESS;    // Exit status
    int err_num = 0;              // Store errno here
    // char *cmdBuff = NULL;         // Buffer to store the command
    // FILE *python_stream = NULL;   // Return value from the call to popen()
    // int temp_char = 0;            // Store characters from the process stream
    wchar_t **wargv = NULL;


    // INPUT VALIDATION
    if (argc < 2)
    {
        status = EXIT_FAILURE;
    }

    // SETUP
    Py_Initialize();

    // EXECUTE PARAMETERS
    // Convert arguments
    if (EXIT_SUCCESS == status)
    {
        wargv = convert_argv_to_wargv(argc, argv);

        if (!wargv)
        {
            status = EXIT_FAILURE;
        }
    }

    // Invoke the main program for the standard Python interpreter
    if (EXIT_SUCCESS == status)
    {
        status = Py_Main(argc, wargv);

        if (status)
        {
            err_num = errno;
            MCC_ERROR(main_libpython, main, Py_Main appears to have failed);
            MCC_ERNUM(main_libpython, Py_Main, status);
            MCC_ERRNO(main_libpython, Py_Main, err_num);
            status = EXIT_FAILURE;  // Resetting return value
        }
        else
        {
            status = EXIT_SUCCESS;  // Resetting return value
        }
    }

    // CLEAN UP
    // wargv
    if (wargv)
    {
        // Free
        free_wargv(argc, wargv);
        // NULL
        wargv = NULL;
    }
    // Python library
    Py_Finalize();

    // DONE
    exit(status);
}
