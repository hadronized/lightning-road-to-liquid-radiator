CXX= clang++
CXXFLAGS= -W -Wall -pedantic -DGL_GLEXT_PROTOTYPES -I./include -std=c++11 -DGLX_GL_CONTEXT
LDFLAGS= -lGL -L/usr/lib/nvidia-bumblebee -lfmodex -lX11
OBJ=main.o common.o shader.o matrix.o bootstrap.o mod0.o mod1.o mod2.o
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
