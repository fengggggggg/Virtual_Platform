SYSTEMC_PATH=/opt/systemc-2.3.1
SYSTEMC_INCLUDE=-I$(SYSTEMC_PATH)/include
SYSTEMC_L_OPTION=-L$(SYSTEMC_PATH)/lib-linux64

CXXFLAGS= $(SYSTEMC_INCLUDE) -std=c++11
LDFLAGS= $(SYSTEMC_L_OPTION) -lsystemc

export CXXFLAGS LDFLAGS

.PHONY: clean all

simulator:at_example.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $<

clean:
	rm -f *.o simulator


