#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'GameBoyEmulator.exe'
# 'make clean'  removes all .o and executable files
#

# define the C++ compiler to use
CXX = g++

# define any compile-time flags
CFLAGS = -Wall

# define any directories containing header files other than /usr/include
#
INCLUDES = -I../include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L../lib

# link to the sfml libraries and tinyxml 
LIBS = -lsfml-system -lsfml-audio -lsfml-graphics -ltinyxml2

# define the C source files
SRCS = Apu.cpp BitFunctions.cpp Cart.cpp CartHeader.cpp Cpu.cpp DebugLog.cpp GameBoy.cpp Gpu.cpp main.cpp MBC.cpp Mmu.cpp OpFuncs.cpp Refference.cpp RomOnly.cpp TableGenerator.cpp Timer.cpp Apu/SquareGenerator.cpp Apu/WaveGenerator.cpp Debugger/Debugger.cpp Instruction/Arithmetic.cpp Instruction/Control.cpp Instruction/Memory.cpp Instruction/OpCodeTable.cpp Video/Pallete.cpp Video/Tile.cpp

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = GameBoyEmulator.exe

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(MAIN)
	@echo  GameBoyEmulator Compiled

$(MAIN): $(OBJS) 
	$(CXX) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it