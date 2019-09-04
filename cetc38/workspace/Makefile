FILE_PATH=/opt
SCROOT=$(FILE_PATH)/systemc-2.3.1/
BOOST_INCLUDE=-I${FILE_PATH}/boost_1_51_0/include
BOOST_L_OPTION=-L${FILE_PATH}/boost_1_51_0/lib


LDFLAGS=  -fno-common  -L$(SCROOT)lib-linux64   -lboost_system -lboost_chrono -lboost_thread   -lsystemc -L$(PWD) -lbwdsp104x 
CXXFLAGS= -c -g -O2 -fPIC -I$(SCROOT)include  -std=c++0x   -I$(PWD)/include -I$(PWD)/include/icache_sim


export CXXFLAGS LDFLAGS SCROOT

.PHONY: clean all

sim:test
test:main.cpp
	$(CXX)  -fPIC -c -g -O0  -I$(SCROOT)include  -I$(PWD)/include -I$(PWD)/include/icache_sim  $(BOOST_INCLUDE)     main.cpp -o main.o
	$(CXX)  main.o  -L$(PWD) $(BOOST_L_OPTION) $(LDFLAGS)  -o simulator2


clean:
	rm -f *.o libmytest.so core.* simulator** 
	rm -rf DSPLog_core0/* DSPLog_core1/*
