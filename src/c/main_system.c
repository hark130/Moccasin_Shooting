// Standard Includes
#include <errno.h>      // errno
#include <stdlib.h>     // MACROS
#include <stdio.h>      // fprintf()
// Local Includes
#include "MOSH_Command_Cat.h"


int main(int argc, char **argv)
{
    // LOCAL VARIABLES
    int status = EXIT_SUCCESS;    // Exit status
    int errNum = 0;               // Store error codes here
    char *cmdBuff = NULL;         // Buffer to store the command

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
            MCC_ERROR(main_system, main, concatenate_arguments appears to have failed);
            MCC_ERNUM(main_system, concatenate_arguments, errNum);
        }
    }

    // Call system
    if (EXIT_SUCCESS == status)
    {
        status = system(cmdBuff);
        if (status)
        {
            errNum = errno;
            MCC_ERROR(main_system, main, pclose appears to have failed);
            MCC_ERNUM(main_system, system, status);
            MCC_ERRNO(main_system, system, errNum);
        }
    }

    // CLEAN UP
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
