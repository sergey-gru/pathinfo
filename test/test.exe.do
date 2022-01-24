#!bash
FNAME=$1
BNAME=$2
TNAME=$3
source ../config.sh

objs="test.o test_path.o ../path.o"

redo-ifchange ${objs}
$CC $CLFAGS $LDFLAGS -o ${TNAME} ${objs}
