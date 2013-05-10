CXX= g++
CXXFLAGS= -W -DGL_GLEXT_PROTOTYPES -I./include -I./include/neon/corelib -I./ -std=c++11 -ffast-math -fgcse -Os -g -DDEBUG
LDFLAGS= -lX11 -lGL -lNeon -lasound -L./lib -pthread
OBJ=main.o gl.o window.o audiodevice.o text_writer.o common.o shader.o matrix.o bootstrap.o mod0.o mod1.o mod2.o mod3.o
INTRO_NAME= lr2lr
EXEC= $(INTRO_NAME).bin
PACKER= $(INTRO_NAME)
COMPRESS_LVL= 6

.PHONY: all, intro, clean, rebuild

all: $(OBJ)
	$(CXX) $^ -o $(EXEC) $(CXXFLAGS) $(LDFLAGS)

intro: all
	strip -s $(EXEC)
	sstrip -z $(EXEC)
	cp packer $(PACKER)
	xz -$(COMPRESS_LVL)ck $(EXEC) >> $(PACKER)
	chmod +x $(PACKER)

main.o: src/main.cpp
	$(CXX) -c $^ -o main.o $(CXXFLAGS)

%.o: src/%.cpp include/%.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

rebuild: clean all

clean:
	@rm -f *.o $(EXEC) $(PACKER)
