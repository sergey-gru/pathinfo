#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='../..'
P_SRC="${P_ROOT}/src"
P_TST="${P_ROOT}/src/test"
P_OBJ="${P_ROOT}/obj"
source ${P_ROOT}/config.sh

redo-ifchange ${P_SRC}/"compile.h"
redo-ifchange ${P_TST}/${BNAME}.c
redo-ifchange ${P_SRC}/${BNAME}.c
redo-ifchange ${P_OBJ}/${BNAME}.o

if [[ -f "${P_SRC}/${BNAME}.h" ]]; then
	redo-ifchange ${P_SRC}/${BNAME}.h
fi

if [[ -f "${P_TST}/${BNAME}.h" ]]; then
	redo-ifchange ${P_TST}/${BNAME}.h
fi

$CC $CFLAGS $LDFLAGS -o ${TNAME} ${P_TST}/${BNAME}.c ${P_OBJ}/${BNAME}.o
