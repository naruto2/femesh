PROG =  femesh
SRCS =	op.c++ \
	solver.c++ \
	femesh.c++ \
	fscanxyc.c++ \
	plotmesh.c++ \
	printmesh.c++ 

OBJS = $(SRCS:.c++=.o)
.SUFFIXES: .c++ .o

CPPFLAGS = -Wall
LDFLAGS = 

.PHONY: all clean

all: $(PROG)

$(PROG) : $(OBJS) 
	c++ main.c++ $(OBJS) -o $@ $(LDFLAGS)

.c++.o:
	c++ $(CPPFLAGS) -c $< 

obj: $(OBJS)
	ar cr libfemesh.a $(OBJS)
	rm *.o

clean :
	rm -f $(OBJS) $(PROG) libfemesh.a 

test: $(PROG)
	./test.sh
