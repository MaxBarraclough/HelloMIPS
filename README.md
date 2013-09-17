HelloMIPS
=========

Playing with int arrays of MIPS machine code: ultra-simple run-time function-generation


About
=====

Tested on Qemu (MIPS/malta).

Although compilation will work for other architectures, execution will cause an error of something like:

    illegal hardware instruction


The MIPS machine-code sequences used (in the static int arrays) are based on output from GCC 4.4.5 for mips-linux-gnu.

