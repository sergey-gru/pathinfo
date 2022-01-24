#!bash
FNAME=$1
BNAME=$2
TNAME=$3
source ./config.sh

objs="main.o path.o options.o ${P_REPO}/sergey-gru/cterm/obj/cterm.o"

redo-ifchange ${objs}
$CC $CLFAGS $LDFLAGS -o ${TNAME} ${objs}
