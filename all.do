#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='.'
source "${P_ROOT}/config.sh"

redo-ifchange "${P_ROOT}/pathinfo.exe"
#redo-ifchange ${P_ROOT}/obj/test/all

