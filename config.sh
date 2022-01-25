#!bash
P_GCC_BIN='C:/cygwin64/bin'
P_REPO="${P_ROOT}/../.."
#Tools
     AS="${P_GCC_BIN}/i686-w64-mingw32-as"
     CC="${P_GCC_BIN}/i686-w64-mingw32-gcc"
    CXX="${P_GCC_BIN}/i686-w64-mingw32-g++"
     LD="${P_GCC_BIN}/i686-w64-mingw32-gcc"
OBJCOPY="${P_GCC_BIN}/i686-w64-mingw32-objcopy"
OBJDUMP="${P_GCC_BIN}/i686-w64-mingw32-objdump"
   SIZE="${P_GCC_BIN}/i686-w64-mingw32-size"

CC='gcc'
CFLAGS="-g -I ${P_REPO}"

redo-ifchange "${P_ROOT}/config.sh"

