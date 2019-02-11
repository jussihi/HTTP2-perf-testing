CPP      = g++
LIBS     = -lnghttp2_asio -lboost_system -lssl -lcrypto -lpthread
CXXFLAGS = -std=c++14 -Wall -g
TESTLIBS = -lboost_chrono -lboost_thread

.PHONY: all clean

all: client server

test: test-server test-multi test-multi-disabled test-push test-push-disabled

server: server.cpp
	$(CPP) server.cpp -o server $(CXXFLAGS) $(LIBS)

client: client.cpp
	$(CPP) client.cpp -o client $(CXXFLAGS) $(LIBS)

test-server: test-server.cpp
	$(CPP) test-server.cpp -o test-server $(CXXFLAGS) $(LIBS) $(TESTLIBS)

test-multi: test-multi.cpp
	$(CPP) test-multi.cpp -o test-multi $(CXXFLAGS) $(LIBS) $(TESTLIBS)

test-multi-disabled: test-multi-disabled.cpp
	$(CPP) test-multi-disabled.cpp -o test-multi-disabled $(CXXFLAGS) $(LIBS) $(TESTLIBS)

test-push: test-push.cpp
	$(CPP) test-push.cpp -o test-push $(CXXFLAGS) $(LIBS) $(TESTLIBS)

test-push-disabled: test-push-disabled.cpp
	$(CPP) test-push-disabled.cpp -o test-push-disabled $(CXXFLAGS) $(LIBS) $(TESTLIBS)

.PHONY : clean
clean : 
	-rm *.o $(objects) server client test-server test-multi test-multi-disabled test-push test-push-disabled *results
