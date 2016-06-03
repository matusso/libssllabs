//
// Created by burso on 6/3/16.
//

#include <python2.7/Python.h>
#include "../../include/ssllabs/ssllabs.h"

extern "C" {
static PyObject *pyssllabs(PyObject *self) {
    return Py_BuildValue("s", "Hello, Python extensions!!");
}

static char ssllabs_docs[] =
        "ssllabs( ): Any message you want to put here!!\n";

static PyMethodDef ssllabs_funcs[] = {
        {"ssllabs", (PyCFunction) pyssllabs, METH_NOARGS, ssllabs_docs},
        {NULL}
};

void init_ssllabs(void) {
    Py_InitModule3("ssllabs", ssllabs_funcs,
                   "Extension module example!");
}
}