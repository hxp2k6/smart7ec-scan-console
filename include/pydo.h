#ifndef PYDO_H
#define PYDO_H

#include <Python.h>

char* pyfile_path(char* path);
char* getDictString(PyObject* pValue,char* str);
int verify_python(char* filepath,char* filename,int mode,char* host,int port);
void verify_python_test(char* filepath,char* filename);
int verify_python_baseline(char* filepath,char* filename);

#endif
