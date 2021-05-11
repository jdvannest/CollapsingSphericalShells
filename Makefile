#
# Flags for optimization:
#
CC := g++
CFLAGS := -g 


#LINKER FLAGS
LFLAGS= -lstdc++ 


#Source files:

OBJ1 := build/Simulation.o
OBJ2 := build/read_params.o
OBJ3 := build/evolve.o
OBJ4 := build/conversions.o
TARGET1 := Simulation

OBJ11 := build/GenerateParamFile.o
TARGET2 := GenerateParamFile



TARGETS := $(TARGET1) $(TARGET2)

all: $(TARGETS)


$(TARGET1):$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET2):$(OBJ11)
	$(CC) $(CFLAGS) $^ -o $@


.PHONY: clean

clean:
	\rm -f build/*.o *.mod *.Data.* *.png *.gif *_*/*.png $(TARGETS) *.lst output.txt

#
# here's how we translate the files:
#

%.o: build/%.cpp Makefile
	$(CC) $(CFLAGS) -c $<

