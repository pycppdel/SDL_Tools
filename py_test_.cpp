#include <iostream>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#pragma comment(lib, "python39.lib")
#pragma comment(lib, "python39_d.lib")
#pragma comment(lib, "python3.lib")
#pragma comment(lib, "python3_d.lib")

int main(){
  /*
  PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *presult;
  pName = Py_BuildValue("s", "a");

  pModule = PyImport_Import(pName);

  pDict = PyModule_GetDict(pModule);

  PyObject *n = Py_BuildValue("(is)", 5, "e");

   // pFunc is also a borrowed reference
   pFunc = PyDict_GetItemString(pDict, (char*)"fak");

  PyObject* result = PyObject_CallObject(pFunc, n);
  int res = PyLong_AsLong(result);
  std::cout << res << std::endl;
  Py_DECREF(pName);
  Py_DECREF(pModule);
  */
  Py_Initialize();

  PyObject* name = Py_BuildValue("s", "a");
  PyObject* module = PyImport_Import(name);
  PyObject* A = PyObject_GetAttrString(module, "A");
  PyObject* names = Py_BuildValue("(s)", "HALLO");
  PyObject* inst = PyEval_CallObject(A, names);
  PyObject* method = PyObject_GetAttrString(inst, "print_");
  PyEval_CallObject(method, NULL);

  Py_DECREF(name);
  Py_DECREF(module);
  Py_Finalize();




  return 0;
}
