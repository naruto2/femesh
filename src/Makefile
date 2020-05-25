PROG =  femesh
SRCS =	op.cpp \
	femesh.cpp \
	fscanxyc.cpp \
	plotmesh.cpp \
	printmesh.cpp \
	gpusolver.cpp \
	solver.cpp 

OBJS = $(SRCS:.cpp=.o)
.SUFFIXES: .cpp .o

CPPFLAGS = -g
LDFLAGS = -lcusolver

.PHONY: all clean

all: $(PROG)

$(PROG) : $(OBJS) 
	/opt/cuda/bin/nvcc main.cpp $(OBJS) -o $@ $(LDFLAGS)

.cpp.o:
	/opt/cuda/bin/nvcc $(CPPFLAGS) -c $< 

obj: $(OBJS)
	ar cr libfemesh.a $(OBJS)
	rm *.o

clean :
	rm -f $(OBJS) $(PROG) libfemesh.a 

test: $(PROG)
	./test.sh
