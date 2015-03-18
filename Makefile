
LDFLAGS  := $(shell wx-config --libs)
CXXFLAGS := -std=c++14 -Wall -Werror $(shell wx-config --cxxflags)
CPPFLAGS :=
OBJS     := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

build: $(OBJS)
	g++ $(OBJS) $(LDFLAGS) -o redres
