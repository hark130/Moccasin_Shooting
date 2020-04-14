// Standard Includes
#include <stdlib.h>     // MACROS
#include <stdio.h>      // fprintf()
#include <string.h>     // memset()
// Local Includes
#include "MOSH_Command_Cat.h"


int main(int argc, char **argv)
{
    // LOCAL VARIABLES
    int status = EXIT_SUCCESS;    // Exit status
    int errNum = 0;               // Store error codes here
    char failMsg[] = {"ERROR:"};  // Standardized failure message
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
            fprintf(stderr, "%s concatenate_arguments appears to have failed with %d\n",
                    failMsg, errNum);
        }
    }

    // Call system
    if (EXIT_SUCCESS == status)
    {
        status = system(cmdBuff);
        if (status)
        {
            fprintf(stderr, "%s system appears to have failed with %d\n",
                    failMsg, status);
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
