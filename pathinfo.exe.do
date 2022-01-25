#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='.'
source ${P_ROOT}/config.sh

CC_OBJS=`ls ${P_ROOT}/src/*.c`
CC_OBJS=${CC_OBJS//.c/.o}
CC_OBJS=${CC_OBJS//src/obj}

CC_OBJS="${CC_OBJS} ${P_REPO}/sergey-gru/cterm/obj/cterm.o"

redo-ifchange ${CC_OBJS}
$CC $CLFAGS $LDFLAGS -o ${TNAME} ${CC_OBJS}
