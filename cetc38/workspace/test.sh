#!/bin/bash 

export LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH
printenv|grep -w LD_LIBRARY_PATH --color
./simulator
