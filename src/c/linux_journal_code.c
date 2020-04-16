/*
 *  This code represents copy/pasted proof-of-concept code from:
 *      https://www.linuxjournal.com/article/8497
 *  This web page is ~15 years old and I want to functionally test
 *      it as-is before I try and adapt it into something more
 *      modern.
 */

// #include <python2.3/Python.h>  /* I don't have Python2.3 */
#include <python2.7/Python.h>


// Listing 1. Embedding Python in Three Lines
void exec_pycode(const char* code)
{
    Py_Initialize();
    PyRun_SimpleString(code);
    Py_Finalize();
}


// Listing 2. Embedding an Interactive Python
void exec_interactive_interpreter(int argc, char** argv)
{
    Py_Initialize();
    Py_Main(argc, argv);
    Py_Finalize();
}


// Listing 4. A Simple Expression Calculator
void process_expression(char* filename,
                        int num,
                        char** exp)
{
    FILE*       exp_file;

    // Initialize a global variable for
    // display of expression results
    PyRun_SimpleString("x = 0");

    // Open and execute the file of
    // functions to be made available
    // to user expressions
    exp_file = fopen(filename, "r");
    PyRun_SimpleFile(exp_file, filename);

    // Iterate through the expressions
    // and execute them
    while(num--) {
        PyRun_SimpleString(*exp++);
        PyRun_SimpleString("print x");
    }
}


// Listing 5. Using Callable Function References
// Originally named void process_expression() but I
//  renamed it here to avoid compiler errors.
void process_function(int num, char* func_name, char* filename)
{
    FILE*        exp_file;
    PyObject*    main_module, * global_dict, * expression;

    // Initialize a global variable for
    // display of expression results
    PyRun_SimpleString("x = 0");

    // Open and execute the Python file
    exp_file = fopen(filename, "r");
    PyRun_SimpleFile(exp_file, filename);

    // Get a reference to the main module
    // and global dictionary
    main_module = PyImport_AddModule("__main__");
    global_dict = PyModule_GetDict(main_module);

    // Extract a reference to the function "func_name"
    // from the global dictionary
    expression =
        PyDict_GetItemString(global_dict, func_name);

    while(num--) {
        // Make a call to the function referenced
        // by "expression"
        PyObject_CallObject(expression, NULL);
    }
    PyRun_SimpleString("print x");
}


int main(int argc, char** argv)
{
    Py_Initialize();

    if(argc != 3) {
        printf("Usage: %s FILENAME EXPRESSION+\n");
        return 1;
    }
    process_expression(argv[1], argc - 1, argv + 2);
    return 0;
}
