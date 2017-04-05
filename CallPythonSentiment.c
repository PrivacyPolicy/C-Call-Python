#include <Python.h>

int main(int argc, char* argv[])
{
  PyObject *pName, *pModule, *pDict, *pFunc;
  PyObject /**pArgs, */*pValue;
  int i;
  
  if (argc < 2) {
    fprintf(stderr, "Usage: pass \"your message like this\"\n");
    return 1;
  }
  
  Py_Initialize();
  // Refer to local file, not python module
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append(\".\")");
  
  pName = PyString_FromString("sentiment"); // file that we're importing
  
  pModule = PyImport_Import(pName);
  Py_DECREF(pName);
  
  if (pModule != NULL) {
    pFunc = PyObject_GetAttrString(pModule, "analyze");
    
    if (pFunc && PyCallable_Check(pFunc)) {
      //pArgs = PyTuple_New(argc - 2);
      pValue = PyString_FromString(argv[1]);
      if (!pValue) {
        //Py_DECREF(pArgs);
        Py_DECREF(pModule);
        fprintf(stderr, "cannot convert arugment");
        return 1;
      }
      pValue = PyObject_CallObject(pFunc, pValue);
      Py_DECREF(pValue);
      if (pValue != NULL) {
        printf("Result: %s\n", PyString_AsString(pValue));
        Py_DECREF(pValue);
      } else {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr, "Call failed\n");
        return 1;
      }
    } else {
      if (PyErr_Occurred()) PyErr_Print();
      fprintf(stderr, "Cannot find function analyze\n");
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
  } else {
    PyErr_Print();
    fprintf(stderr, "Failed to load 'sentiment.py'\n");
    return 1;
  }
  Py_Finalize();
  return 0;
}    
