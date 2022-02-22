#!bash

# !!!! before doing this script you MUST to set P_ROOT variable
P_REPO="${P_ROOT}/../.."
P_SRC="${P_ROOT}/src"
P_OBJ="${P_ROOT}/obj"
P_INCLUDE="${P_ROOT}/include"
P_SRC_TEST="${P_SRC}/test"
P_OBJ_TEST="${P_OBJ}/test"

redo-ifchange "${P_ROOT}/config.sh"


P_GCC_BIN='C:/cygwin64/bin'
#Tools
     AS="${P_GCC_BIN}/i686-w64-mingw32-as"
     CC="${P_GCC_BIN}/i686-w64-mingw32-gcc"
    CXX="${P_GCC_BIN}/i686-w64-mingw32-g++"
     LD="${P_GCC_BIN}/i686-w64-mingw32-gcc"
OBJCOPY="${P_GCC_BIN}/i686-w64-mingw32-objcopy"
OBJDUMP="${P_GCC_BIN}/i686-w64-mingw32-objdump"
   SIZE="${P_GCC_BIN}/i686-w64-mingw32-size"

CC='gcc'
CFLAGS="-g -I${P_REPO} -I${P_INCLUDE} `pkg-config --cflags glib-2.0`"
LIBS="`pkg-config --libs glib-2.0`"
