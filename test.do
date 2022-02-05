#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='.'
P_OBJ="${P_ROOT}/obj"
source "${P_ROOT}/config.sh"

redo-ifchange "${P_OBJ}/test/all" "${P_OBJ}/test_sys/all"
