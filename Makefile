CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I$(SYSTEMC_PATH)/include
LDFLAGS = -L$(SYSTEMC_PATH)/lib -lsystemc
LDLIBPATH = LD_LIBRARY_PATH=$(SYSTEMC_PATH)/lib

SRC := $(wildcard src/*.cpp)
TESTS := $(wildcard tests/*.cpp)
OBJS := $(patsubst tests/%.cpp, build/test_%, $(TESTS))

build:
	mkdir -p build

build/test_%: tests/%.cpp $(SRC) | build
	$(CXX) $(CXXFLAGS) $< $(SRC) $(LDFLAGS) -o $@

all: $(OBJS)

run-%: build/test_%
	$(LDLIBPATH) $< $(size) $(alg) $(pkg_cnt)

clean:
	rm -rf build

run-loader: loader.cpp $(SRC) | build
	$(CXX) $(CXXFLAGS) $< $(SRC) $(LDFLAGS) -o $@
