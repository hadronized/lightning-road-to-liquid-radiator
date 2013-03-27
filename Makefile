CXX= clang++
CXXFLAGS= -W -Wall -pedantic -DGL_GLEXT_PROTOTYPES
LDFLAGS= -lSDL -lGL
OBJ=main.o
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
