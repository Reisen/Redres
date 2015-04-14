LDFLAGS  := $(shell wx-config --libs)
CXXFLAGS := -std=c++14 -Wall -Werror $(shell wx-config --cxxflags)
CPPFLAGS :=
OBJS     := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJS     += $(patsubst %.cpp, %.o, $(wildcard ui/*.cpp))

.PHONY: build
build: $(OBJS)
	g++ $(OBJS) $(LDFLAGS) -o redres

.PHONY: clean
clean:
	-find ./ -name "*.o" -exec rm {} \;
	-rm redres

