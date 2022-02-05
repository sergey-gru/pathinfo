#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='../..'
P_TST="${P_ROOT}/obj/test"
source ${P_ROOT}/config.sh

redo-ifchange ${P_TST}/${BNAME}.exe

${P_TST}/${BNAME}.exe > ${TNAME}

