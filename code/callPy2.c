// Reference
// BingAI

#include <Python.h>

int main(int argc, char *argv[]) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    // Initialize the Python interpreter
    Py_Initialize();
    PyObject *sys      = PyImport_ImportModule("sys");
    PyObject *sys_path = PyObject_GetAttrString(sys, "path");
    PyList_Append(sys_path, PyUnicode_DecodeFSDefault("."));
    // Build the name object
    pName = PyUnicode_FromString("pytest");

    // Load the module object
    pModule = PyImport_Import(pName);

    // Clean up
    Py_DECREF(pName);

    if (pModule != NULL) {
        // Get the function object
        pFunc = PyObject_GetAttrString(pModule, "hello");

        if (pFunc && PyCallable_Check(pFunc)) {
            // Build the argument list
            pArgs = PyTuple_New(2);
            pValue = PyLong_FromLong(1);
            PyTuple_SetItem(pArgs, 0, pValue);
            pValue = PyLong_FromLong(2);
            PyTuple_SetItem(pArgs, 1, pValue);

            // Call the function
            pValue = PyObject_CallObject(pFunc, pArgs);

            // Clean up
            Py_DECREF(pArgs);

            if (pValue != NULL) {
                Py_ssize_t size = 100;
                printf("Result of call: %s\n", PyUnicode_AsUTF8AndSize(pValue, &size));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"hello\"\n");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"pytest\"\n");
        return 1;
    }
    // Finish the Python interpreter
    Py_Finalize();
    return 0;
}
