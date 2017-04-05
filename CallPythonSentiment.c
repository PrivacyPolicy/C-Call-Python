#include <Python.h>

float getSentiment();

int main(int argc, char* argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Usage: call this file with a sentence in quotes to analyze.\n");
  }
  fprintf(stdout, "sentiment: %f\n", getSentiment(argv[1]));
}

float getSentiment(char* sentence)
{
  PyObject *pName, *pModule, *pDict, *pFunc;
  PyObject *pArgs, *pValue;
  int i;
  
  Py_Initialize();
  // Refer to local file, not python module
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append(\".\")");
  PyRun_SimpleString("from sentimentweb.info import feature_selection_trials, MyDict, classify2");

  pName = PyString_FromString("sentiment");
  // error checking should occur

  pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  if (pModule != NULL) {
    pFunc = PyObject_GetAttrString(pModule, "analyze");
    // pFunc is a new reference

    if (pFunc && PyCallable_Check(pFunc)) {
      pArgs = PyTuple_New(1);
      pValue = PyString_FromString(sentence);
      if (!pValue) {
        Py_DECREF(pArgs);
        Py_DECREF(pModule);
        fprintf(stderr, "Cannot convert argument\n");
        return 1;
      }
      // pValue reference stolen here:
      PyTuple_SetItem(pArgs, 0, pValue);
      pValue = PyObject_CallObject(pFunc, pArgs);
      Py_DECREF(pArgs);
      if (pValue != NULL) {
        int positive = PyTuple_GetItem(pValue, 0) == Py_True;
        double probability = PyFloat_AsDouble(PyTuple_GetItem(pValue, 1));
        //printf("Result of call: %o\n", PyTuple_AsTuple(pValue));
        printf("Sentiment is: %s. Probability is: %0.3f.\n",
            (positive) ? "positive" : "negative", probability);
        double d = ((positive) ? 1 : -1) * probability;
        if (d > 1) d = 1;
        if (d < -1) d = -1;
        Py_DECREF(pValue);
        return d;
      }
      else {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr, "Call failed\n");
        return 1;
      }
    } else {
      if (PyErr_Occurred())
        PyErr_Print();
      fprintf(stderr, "Cannot find function analyze.\n");
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
  } else {
    PyErr_Print();
    fprintf(stderr, "Failed to comprehend \"%s\", I guess.\n", sentence);
    return 1;
  }
  Py_Finalize();
  return 0;
}
