#include <stdlib.h>     // size_t, MACROS, calloc()
#include <stdio.h>      // printf(), fprintf(), putchar()
#include <string.h>     // strlen()


int main(int argc, char** argv)
{
    // LOCAL VARIABLES
    int status = EXIT_SUCCESS;    // Exit status
    int i = 0;                    // Iterating variable
    size_t buffLen = 0;           // Total length of all concatenated commands
    char failMsg[] = {"ERROR:"};  // Standardized failure message
    char *cmdBuff = NULL;         // Buffer to store the command
    char *tmpBuff = NULL;         // Temporary pointer to iterate

    // INPUT VALIDATION
    if (argc < 2)
    {
        status = EXIT_FAILURE;
    }

    // EXECUTE PARAMETERS
    // Determine buffer length
    if (EXIT_SUCCESS == status)
    {        
        for (i = 1; i < argc; i++)
        {
            // printf("%s ", (*(argv+i)));  // DEBUGGING
            buffLen += strlen((*(argv+i)));  // Command length
            buffLen += 1;  // Room for space or nul-terminator
        }

    }

    // Allocate memory
    if (EXIT_SUCCESS == status)
    {
        cmdBuff = calloc(buffLen, sizeof(char));
        tmpBuff = cmdBuff;

        if (!cmdBuff)
        {
            fprintf(stderr,
                    "%s calloc has failed to allocate memory\n", failMsg);
            status = EXIT_FAILURE;
        }
    }

    // Copy in commands
    if (EXIT_SUCCESS == status)
    {
        for (i = 1; i < argc; i++)
        {
            if (tmpBuff != strcpy(tmpBuff, (*(argv+i))))
            {
                fprintf(stderr, "%s strcpy has failed\n", failMsg);
                status = EXIT_FAILURE;
                break;
            }
            else
            {
                // Advance the pointer past the string that got copied in
                tmpBuff += (strlen((*(argv+i))) * sizeof(char));
                // Delimit the concatenated string
                if (i < (argc - 1))
                {
                    // There are more commands to copy in
                    *tmpBuff = ' ';  // Add a space
                    tmpBuff++;  // Advance to the next position
                }
                // else {}  // cmdBuff was calloc'd so it's already terminated
            }
        }
    }

    // Call system
    if (EXIT_SUCCESS == status)
    {
        // putchar(0xA);  // DEBUGGING
        // printf("The command string:  %s\n", cmdBuff);  // DEBUGGING
        // DEBUGGING
        // printf("The final character: '%c' (0x%x)\n",
        //        (*(cmdBuff + ((strlen(cmdBuff) - 1) * sizeof(char)))),
        //        (*(cmdBuff + ((strlen(cmdBuff) - 1) * sizeof(char)))));
        // putchar(0xA);  // DEBUGGING
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
        // Zeroize
        if (cmdBuff != memset(cmdBuff, 0x0, buffLen * sizeof(char)))
        {
            fprintf(stderr, "%s memset has failed\n", failMsg);
            status = EXIT_FAILURE;
        }
        // Free
        free(cmdBuff);
        // NULL
        cmdBuff = NULL;
        tmpBuff = NULL;
    }

    // DONE
    exit(status);
}
