/*
 *  This code represents copy/pasted proof-of-concept code from:
 *      https://www.linuxjournal.com/article/8497
 *  This web page is ~15 years old and I want to functionally test
 *      it as-is before I try and adapt it into something more
 *      modern.
 *  I updated the proof-of-concept code for Python 3.6 with an
 *      eye for sending Python modules to the interpreter.
 */

#include <python3.6/Python.h>


// Adjusted Usage - Just process a file
void process_file(char *filename)
{
    FILE *python_file = NULL;

    // Open and execute the file of
    // functions to be made available
    // to user expressions
    python_file = fopen(filename, "r");

    if (python_file)
    {
        PyRun_SimpleFile(python_file, filename);
        fclose(python_file);
        python_file = NULL;
    }
}

// Lifted from:
// https://stackoverflow.com/questions/31271158/cannot-convert-char-to-wchar-t
wchar_t **convert_argv_char_to_wchar(int argc, char **argv)
{
    wchar_t **changed_argv = NULL;

    changed_argv = calloc(argc + 1, sizeof(wchar_t *));

    fprintf(stderr, "Allocated wchart_t **: %p\n", changed_argv);  // DEBUGGING
    for (int i = 0; i < argc; i++)
    {
        changed_argv[i] = calloc(strlen(argv[i]) + 1, sizeof(wchar_t));
        fprintf(stderr, "Copying %p into %p\n", argv[i], changed_argv[i]);  // DEBUGGING
        mbstowcs(changed_argv[i], argv[i], strlen(argv[i]) + 1);
    }

    return changed_argv;
}


void process_file_wargs(char *filename, int argc, wchar_t **argv)
{
    // FILE *python_file = NULL;

    // python_file = fopen(filename, "r");

    // if (python_file)
    {
        fprintf(stderr, "Executing Py_Main()\n");  // DEBUGGING
        Py_Main(argc, argv);
        // fprintf(stderr, "Executing PyRun_SimpleFile()\n");  // DEBUGGING
        // PyRun_SimpleFile(python_file, filename);
        // fclose(python_file);
        // python_file = NULL;
    }
}


// Process a file along with arguments
// void process_file_args(wchar_t *filename, int argc, wchar_t **argv)
void process_file_args(char *filename, int argc, char **argv)
{
    wchar_t **changed_argv = convert_argv_char_to_wchar(argc, argv);

    if (changed_argv)
    {
        process_file_wargs(filename, argc, changed_argv);

        // Cleanup
        for (int i = 0; i < argc; i++)
        {
            if (changed_argv[i])
            {
                fprintf(stderr, "Freeing %p\n", changed_argv[i]);  // DEBUGGING
                free(changed_argv[i]);
                changed_argv[i] = NULL;
            }
        }
        fprintf(stderr, "Freeing %p\n", changed_argv);  // DEBUGGING
        free(changed_argv);
        changed_argv = NULL;
    }
}


// int wmain(int argc, wchar_t **argv)
int main(int argc, char **argv)
{
    Py_Initialize();

    /* MY CODE */
    if (argc != 2)
    {
        // fprintf(stderr, "USAGE: %ls FILENAME.py\n", argv[0]);
        fprintf(stderr, "USAGE: %s FILENAME.py\n", argv[0]);
        return 1;
    }
    else
    {
        // process_file(argv[1]);
        process_file_args(argv[1], argc, argv);
    }

    Py_Finalize();
    return 0;
}
