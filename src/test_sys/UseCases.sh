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




# Test 
T_PATH='/a/b/c.tar.gz'
TASK="${P_APP} -a ${T_PATH}"
declare RES=`${TASK}`

RES=`${TASK}`
ASSERT=""

















# Testing output types
# depends of count of options
# and -o --out-type option



# No output option
# One output
# Two outputs or more

# Zero params prints usage









# Simple call demonstrates all power --out-type=hash
TASK="${P_APP} ${T_PATH}"
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







# pathinfo -O ${T_PATH}
# RES=`pathinfo -n ${T_PATH}`
# pathinfo 


echo "Errors: ${ERRS}/${CNT}" >&2

