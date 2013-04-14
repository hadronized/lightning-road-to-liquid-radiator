CXX= g++
CXXFLAGS= -W -Wall -pedantic -DGL_GLEXT_PROTOTYPES -I./include -std=c++11 -Os
LDFLAGS= -lSDL -lGL -L/usr/lib/nvidia-bumblebee -lfmodex
OBJ=main.o common.o shader.o matrix.o bootstrap.o mod0.o mod1.o
EXEC= d01

.PHONY: all, clean

all: $(OBJ)
	$(CXX) $^ -o $(EXEC) $(CXXFLAGS) $(LDFLAGS)

main.o: src/main.cpp
	$(CXX) -c $^ -o main.o $(CXXFLAGS)

%.o: src/%.cpp include/%.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f *.o $(EXEC)
