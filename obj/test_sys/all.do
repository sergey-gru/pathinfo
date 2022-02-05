#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='../..'
source ${P_ROOT}/config.sh
P_SRC="${P_ROOT}/src/test_sys"

F_RES=`ls ${P_SRC}/*.sh`
F_RES=${F_RES//.sh/.log}
F_RES=${F_RES//src/obj}

redo-ifchange ${F_RES}
