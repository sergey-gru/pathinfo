#!bash
FNAME=$1
BNAME=$2
TNAME=$3
P_ROOT='..'
P_SRC="${P_ROOT}/src"
source ${P_ROOT}/config.sh


CC_SRC=`ls ${P_SRC}/*.h`
redo-ifchange ${CC_SRC}

redo-ifchange doxygen.cfg 

doxygen doxygen.cfg
