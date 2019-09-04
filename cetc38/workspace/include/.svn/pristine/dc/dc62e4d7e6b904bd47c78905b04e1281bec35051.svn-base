#!/bin/bash
 #edit by wangqiang for indicate DSPLog_core path 
if [ $# -eq 0  ]; then
	echo "DSPlog_core's path is undefined!!"
	echo "you can use . or ~  or other path"
	exit 1
elif [ $# -gt 1 ]; then
	echo "Too many args!"
	exit 1
elif [ ! -d $1 ]; then
	echo "given path not exist!"
	exit 1	
fi
Logpath=$1
LINUX_WIN32_PATH=./src/AlgoriLib
touch sedfile
echo "/\/tmp\/DSPLog\/DSPLog_core/  c\\" >sedfile
echo "			sprintf(m_arrLogDir,\"$Logpath/DSPLog_core%d\",i);" >> sedfile
touch dsp_top_tmp
sed -f sedfile dsp_top.h > dsp_top_tmp
cat dsp_top_tmp>dsp_top.h
rm -rf sedfile dsp_top_tmp
mkdir $Logpath/DSPLog_core0
mkdir $Logpath/DSPLog_core1

echo  "dsp_top.h is mod over, and log file are in $Logpath/DSPLog_core*"

touch sedfile
echo "/#define DSP_WIN32/  c\\//#define DSP_WIN32" >sedfile
echo "/#define DSP_LINUX/  c\\#define DSP_LINUX " >> sedfile
touch dsptypes_tmp
sed -f sedfile $LINUX_WIN32_PATH/dsptypes.h > dsptypes_tmp
cat dsptypes_tmp>$LINUX_WIN32_PATH/dsptypes.h
rm -rf sedfile dsptypes_tmp

echo "$LINUX_WIN32_PATH/dsptypes.h is mod over"





echo "done! you can make to get simulator"
