#!/usr/bin/python3
from ctypes import *
import sys

def wc_py(argc, argv)
    wclink = CDLL("../libs/libcore.so")
    wc = wclink.wc

    LP_c_char = POINTER(c_char)
    LP_LP_c_char = POINTER(LP_c_char)

    wc.argtypes = (c_int, # argc
                         LP_LP_c_char) # argv

    argc = len(sys.argv);
    argv = (LP_c_char * (argc + 1))()

    for i, arg in enumerate(sys.argv):
        enc_arg = arg.encode('utf-8')
        argv[i] = create_string_buffer(enc_arg)

    wc(argc, argv)
