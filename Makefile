LDFLAGS  := $(shell wx-config --libs)
CXXFLAGS := -std=c++14 -Wall -Werror $(shell wx-config --cxxflags)
CPPFLAGS := -I. -L.
OBJS     := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJS     += $(patsubst %.cpp, %.o, $(wildcard ui/*.cpp))
OBJS     += $(patsubst %.cpp, %.o, $(wildcard types/*.cpp))

.PHONY: build
build: $(OBJS)
	g++ $(OBJS) $(LDFLAGS) -o redres

.PHONY: clean
clean:
	-find ./ -name "*.o" -exec rm {} \;
	-rm redres

