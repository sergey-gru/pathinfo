#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='../..'
P_TST="${P_ROOT}/src/test"
source ${P_ROOT}/config.sh

F_TXT=`ls ${P_TST}/*.c`
F_TXT=${F_TXT//.c/.log}
F_TXT=${F_TXT//src/obj}

redo-ifchange ${F_TXT}
