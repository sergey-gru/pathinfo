#!bash
P_ROOT='../..'
P_TST="${P_ROOT}/obj/test_sys"

CNT=0

mytest()
{
	echo -e "${CNT}. Task:\n${TASK}"
	echo -e "${CNT}. Assert:\n${ASSERT}"
	echo -e "${CNT}. Res:\n${RES}"

	if [ "${RES}" = "${ASSERT}" ]; then
		echo 'OK'
	else
		echo 'ERR'
		ERRS=$((ERRS + 1))
	fi
	echo ''
	
	CNT=$((CNT + 1))
}

ERRS=0

# Testing cases when "short Single output Option" set
# options: -apdDnbestT
# At theese cases app should output
#   only value of variable without varname
# And a few variables otherwise

# This rules needs for easy using with bash folowing way
# Example: res=`pathinfo -D /a/b/c`
# Example: res=`echo ('a' 'b')`

T_PATH='/a/b/c.tar.gz'

TASK="${P_ROOT}/pathinfo.exe -a ${T_PATH}"
RES=`$TASK`
ASSERT="['path']='/a/b/c' ['dir']='/a/b' ['dirs']=\"'' 'a' 'b'\" ['name']='c' ['bname']='c.tar' ['short']='c' ['tag']='tar.gz' ['tags']=\"'gz' 'tar'\""
mytest

TASK="${P_ROOT}/pathinfo.exe --all ${T_PATH}"
RES=`$TASK`
ASSERT="path='/a/b/c'
dir='/a/b'
dirs=('' 'a' 'b')
name='c'
bname='c.tar'
short='c'
tag='tar.gz'
tags=('gz' 'tar')"
mytest

TASK="${P_ROOT}/pathinfo.exe -p ${T_PATH}"
RES=`$TASK`
ASSERT="'/a/b/c'"
mytest

TASK="${P_ROOT}/pathinfo.exe --path ${T_PATH}"
RES=`$TASK`
mytest


TASK="${P_ROOT}/pathinfo.exe -d ${T_PATH}"
RES=`$TASK`
ASSERT="'/a/b'"
mytest

TASK="${P_ROOT}/pathinfo.exe --dir ${T_PATH}"
RES=`$TASK`
mytest


TASK="${P_ROOT}/pathinfo.exe -D ${T_PATH}"
RES=`$TASK`
ASSERT="('' 'a' 'b')"
mytest

TASK="${P_ROOT}/pathinfo.exe --dirs ${T_PATH}"
RES=`$TASK`
mytest


TASK="${P_ROOT}/pathinfo.exe -n ${T_PATH}"
RES=`$TASK`
ASSERT="'c.tar.gz'"
mytest

TASK="${P_ROOT}/pathinfo.exe --name ${T_PATH}"
RES=`$TASK`
mytest


TASK="${P_ROOT}/pathinfo.exe -b ${T_PATH}"
RES=`$TASK`
ASSERT="'c.tar'"
mytest

TASK="${P_ROOT}/pathinfo.exe --bname ${T_PATH}"
RES=`$TASK`
mytest


TASK="${P_ROOT}/pathinfo.exe -e ${T_PATH}"
RES=`$TASK`
ASSERT="'gz'"
mytest

TASK="${P_ROOT}/pathinfo.exe --ext ${T_PATH}"
RES=`$TASK`
mytest


TASK="${P_ROOT}/pathinfo.exe -s ${T_PATH}"
RES=`$TASK`
ASSERT="short='c'"
mytest

TASK="${P_ROOT}/pathinfo.exe --short ${T_PATH}"
RES=`$TASK`
mytest


TASK="${P_ROOT}/pathinfo.exe -t ${T_PATH}"
RES=`$TASK`
ASSERT="tag='tar.gz'"
mytest

TASK="${P_ROOT}/pathinfo.exe --tag ${T_PATH}"
RES=`$TASK`
mytest


TASK="${P_ROOT}/pathinfo.exe -T ${T_PATH}"
RES=`$TASK`
ASSERT="tags=('gz' 'tar')"
mytest

TASK="${P_ROOT}/pathinfo.exe --tags ${T_PATH}"
RES=`$TASK`
mytest


echo "Errors: ${ERRS}/${CNT}" >&2

