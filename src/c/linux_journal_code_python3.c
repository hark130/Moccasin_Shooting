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


int main(int argc, char** argv)
{
    Py_Initialize();

    /* MY CODE */
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: %s FILENAME.py\n", argv[0]);
        return 1;
    }
    else
    {
        process_file(argv[1]);
    }

    Py_Finalize();
    return 0;
}
