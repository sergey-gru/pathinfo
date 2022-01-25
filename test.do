#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='.'
source ${P_ROOT}/config.sh

redo-ifchange pathinfo.exe test/test.exe

test/test.exe
