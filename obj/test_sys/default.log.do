#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='../..'
source ${P_ROOT}/config.sh
P_SRC="${P_ROOT}/src/test_sys"

redo-ifchange ${P_ROOT}/pathinfo.exe
redo-ifchange ${P_ROOT}/obj/test/all
redo-ifchange ${P_SRC}/${BNAME}.sh

${P_SRC}/${BNAME}.sh > ${TNAME}
