#!/bin/bash

rm -rf libbwdsp104x.so include main.cpp 

curr=`pwd`
SIMSRC=../rapidIO_test

cd  $SIMSRC
make clean
make -j 16
cd $curr



cp  $SIMSRC/libbwdsp104x.so  .
cp  $SIMSRC/main.cpp .
cp  -r  $SIMSRC  .
mv  ./rapidIO_test  ./include  #change the dir name
cd ./include 
python -c 'import os;[os.remove(iter) for iter in  [os.path.join(thisdir,y) for (thisdir,subdir,files) in os.walk(os.getcwd()) for y in files  if y.endswith(".cpp")or y.endswith(".o")]]'  #del the cpp and object files

python -c 'import os;[os.remove(iter) for iter in  [os.path.join(thisdir,y) for (thisdir,subdir,files) in os.walk(os.getcwd()) for y in files  if y.endswith("Makefile")]]'             #del the Makefile



cd ..
make clean
make 
export LD_LIBRARY_PATH=`pwd`:/home/KernelShare/boost_1_51_0/stage/lib:$LD_LIBRARY_PATH
./simulator

