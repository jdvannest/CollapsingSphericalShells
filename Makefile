
#
# Flags for optimization:
#
CC := g++
CFLAGS := -g -fopenmp
FC := gfortran
FFLAGS := -g -fopenmp

#LINKER FLAGS
LFLAGS= -lstdc++ #-lgfortran


#Source files:

OBJ1 := Simulation.o
OBJ2 := read_params.o
OBJ3 := evolve.o
OBJ4 := conversions.o
TARGET1 := Simulation

OBJ11 := GenerateParamFile.o
TARGET2 := GenerateParamFile



TARGETS := $(TARGET1) $(TARGET2)

all: $(TARGETS)


$(TARGET1):$(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
	$(CC) $(CFLAGS) $^ -o $@ -fopenmp

$(TARGET2):$(OBJ11)
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
