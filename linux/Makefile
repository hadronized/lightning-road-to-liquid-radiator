CXX     := g++
CCFLAGS := -I../../corelib/include -ffast-math -fgcse -O2 -s
LDFLAGS := -L../../corelib/lib -lNeon -lasound

SRC     := main.cpp audiodevice.cpp
OUT     := neon_elf32

all:
	$(CXX) $(CCFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)
	@echo "  Uncompressed size: `ls -al neon_elf32 | cut -d' ' -f5` bytes"
	@./xzexe neon_elf32
	@echo "  Compressed size:   `ls -al neon_elf32 | cut -d' ' -f5` bytes"
	@echo
	@echo "  >>> `echo 32768 - \`ls -al neon_elf32 | cut -d' ' -f5\` | bc` bytes still available"


.PHONY: clean

clean:
	@echo "   Cleaning standalone/linux"
	@rm -rf bin/$(OUT)
