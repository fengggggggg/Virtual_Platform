SYSTEMC_PATH=/opt/systemc-2.3.1
SYSTEMC_INCLUDE=-I$(SYSTEMC_PATH)/include
SYSTEMC_L_OPTION=-L$(SYSTEMC_PATH)/lib-linux64

CXX = g++ -std=c++11 -Wall -g -O2
CXXFLAGS= $(SYSTEMC_INCLUDE)
LDFLAGS= $(SYSTEMC_L_OPTION) -lsystemc

targ = simulator
obj = initiator.cpp target.cpp top.cpp router.cpp centralized_buffer.cpp circular_buffer.cpp

export CXXFLAGS LDFLAGS

$(targ) : $(obj)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(targ) $(obj)

.PHONY : clean
clean:
	rm -f *.o $(targ)


