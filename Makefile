
#
# Flags for optimization:
#
CC := g++
CFLAGS := -g 
FC := gfortran
FFLAGS := -g

#LINKER FLAGS
LFLAGS= -lstdc++ #-lgfortran


#Source files:

OBJ1 := Simulation.o
OBJ2 := read_params.o
OBJ3 := evolve.o
TARGET1 := Simulation



TARGETS := $(TARGET1) 

all: $(TARGETS)


$(TARGET1):$(OBJ1) $(OBJ2) $(OBJ3)
	$(CC) $(CFLAGS) $^ -o $@




.PHONY: clean

clean:
	\rm -f *.o *.mod *.Data.* *.png *.gif *_*/*.png $(TARGETS) *.lst output.txt

#
# here's how we translate the files:
#

%.o: %.cpp Makefile
	$(CC) $(CFLAGS) -c $<
%.o: %.f90 Makefile
	$(FC) $(FFLAGS) -c $< 
