#!bash
P_ROOT='../..'
P_TST="${P_ROOT}/obj/test_sys"
P_APP="${P_ROOT}/pathinfo.exe"

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

T_PATH='/a/b/c.tar.gz'


# Testing output types
# depends of count of options
# and -o --out-type option


# --out-type=text
# 1 option
TASK="${P_APP} -p --out-type=text ${T_PATH}"
RES=`$TASK`
ASSERT="/a/b/c.tar.gz"
mytest
# --out-type=text
# 2 option
TASK="${P_APP} -p --out-type=text ${T_PATH}"
RES=`$TASK`
ASSERT='/a/b/c'
mytest


# --out-type=var
# 1 option
TASK="${P_APP} -p --out-type=var ${T_PATH}"
RES=`$TASK`
ASSERT="path='/a/b/c'"
mytest
# --out-type=var
# 2 option
TASK="${P_APP} -p --out-type=var ${T_PATH}"
RES=`$TASK`
ASSERT="path='/a/b/c'"
mytest


# --out-type=hash
# 1 option
TASK="${P_APP} -p --out-type=hash ${T_PATH}"
RES=`$TASK`
ASSERT="path='/a/b/c'"
mytest
# --out-type=hash
# 2 option
TASK="${P_APP} -p --out-type=hash ${T_PATH}"
RES=`$TASK`
ASSERT="path='/a/b/c'"
mytest


# 1 option default --out-type=text
TASK="${P_ROOT}/pathinfo.exe -p ${T_PATH}"
RES=`$TASK`
ASSERT="/a/b/c.tar.gz"
mytest
# 2 option default --out-type=text
TASK="${P_ROOT}/pathinfo.exe -p ${T_PATH}"
RES=`$TASK`
ASSERT="/a/b/c"
mytest
# Simple taking one parameter -> --out-type=var
TASK="${P_ROOT}/pathinfo.exe ${T_PATH}"
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



echo "Errors: ${ERRS}/${CNT}" >&2

