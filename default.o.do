#!bash
FNAME=$1
BNAME=$2
TNAME=$3
source ./config.sh

redo-ifchange ${BNAME}.c ${BNAME}.h "compile.h" "${P_REPO2}/sergey-gru/cterm/cterm.h"
$CC $CFLAGS $LDFLAGS -o ${TNAME} -c ${BNAME}.c
