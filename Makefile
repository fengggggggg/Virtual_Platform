SYSTEMC_PATH=/opt/systemc-2.3.1
SOCLIB_PATH=/opt/soclib/soclib/lib/tlmdt
VCI_SOURCE=/opt/soclib/soclib/communication/vci/tlmt/source/
SYSTEMC_INCLUDE=-I$(SYSTEMC_PATH)/include -I$(SOCLIB_PATH)/include -I$(VCI_SOURCE)/include
SYSTEMC_L_OPTION=-L$(SYSTEMC_PATH)/lib-linux64

CXX = g++ -std=c++11 -w -g -O2
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


