#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='.'
source "${P_ROOT}/config.sh"

rm ${P_OBJ}/*.o 2> /dev/null
rm ${P_OBJ}/test*/*.exe 2> /dev/null
rm ${P_OBJ}/test*/*.log 2> /dev/null

rm ${P_OBJ}/src/*.o 2> /dev/null
rm -d ${P_OBJ}/src 2> /dev/null

true
