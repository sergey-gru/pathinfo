#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='..'
P_SRC="${P_ROOT}/src"
source "${P_ROOT}/config.sh"

redo-ifchange "${P_SRC}/compile.h"
redo-ifchange "${P_SRC}/${BNAME}.c"

if [[ -f "${P_SRC}/${BNAME}.h" ]]; then
	redo-ifchange "${P_SRC}/${BNAME}.h"
fi

$CC $CFLAGS $LDFLAGS -o ${TNAME} -c "${P_SRC}/${BNAME}.c"
