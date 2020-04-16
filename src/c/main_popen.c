// Standard Includes
#include <errno.h>      // errno
#include <stdlib.h>     // MACROS
// Local Includes
#include "MOSH_Command_Cat.h"


int main(int argc, char **argv)
{
    // LOCAL VARIABLES
    int status = EXIT_SUCCESS;    // Exit status
    int errNum = 0;               // Store error codes here
    char *cmdBuff = NULL;         // Buffer to store the command
    FILE *python_stream = NULL;   // Return value from the call to popen()
    int temp_char = 0;            // Store characters from the process stream

    // INPUT VALIDATION
    if (argc < 2)
    {
        status = EXIT_FAILURE;
    }

    // EXECUTE PARAMETERS
    // Concatenate the parameters
    if (EXIT_SUCCESS == status)
    {
        cmdBuff = concatenate_arguments(argc, argv, 1, argc - 1, &errNum);

        if (!cmdBuff || 0x0 == *cmdBuff)
        {
            status = EXIT_FAILURE;
            MCC_ERROR(main_popen, main, concatenate_arguments appears to have failed);
            MCC_ERNUM(main_popen, concatenate_arguments, errNum);
        }
    }

    // Call popen
    if (EXIT_SUCCESS == status)
    {
        python_stream = popen(cmdBuff, "r");

        if (!python_stream)
        {
            errNum = errno;
            status = EXIT_FAILURE;
            MCC_ERROR(main_popen, main, popen appears to have failed);
            MCC_ERRNO(main_popen, popen, errNum);
        }
    }

    // Read the stream
    if (EXIT_SUCCESS == status)
    {
        while (1)
        {
            temp_char = fgetc(python_stream);

            if (temp_char != EOF)
            {
                putchar(temp_char);
            }
            else
            {
                break;
            }
        }
    }

    // CLEAN UP
    // popen's file stream
    if (python_stream)
    {
        status = pclose(python_stream);

        if (status)
        {
            errNum = errno;
            MCC_ERROR(main_popen, main, pclose appears to have failed);
            MCC_ERNUM(main_popen, pclose, status);
            MCC_ERRNO(main_popen, pclose, errNum);
        }
    }

    // Heap-allocated buffer
    if (cmdBuff)
    {
        // Free
        free(cmdBuff);
        // NULL
        cmdBuff = NULL;
    }

    // DONE
    exit(status);
}
