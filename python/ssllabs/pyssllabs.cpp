//
// Created by burso on 6/3/16.
//

#include "../../include/ssllabs/ssllabs.h"
#include <python2.7/Python.h>

extern "C" {
    #include <iostream>

    static PyObject *getInfo(PyObject *self) {
        std::string data;
        ssllabs::SSLlabs sslabs;

        sslabs.getInfo(data);
        return Py_BuildValue("s", data.c_str());
    }

    static char ssllabs_docs[] =
            "ssllabs( ): Any message you want to put here!!\n";

    static PyMethodDef ssllabs_funcs[] = {
            {"getInfo", (PyCFunction) getInfo, METH_NOARGS, ssllabs_docs},
            {NULL, NULL, 0, NULL}
    };

    void initssllabs(void) {
        Py_InitModule3("ssllabs", ssllabs_funcs,
                       "Extension module example!");
    }
}
