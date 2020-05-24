PROG =  femesh
SRCS =	rotate_right.c++ \
	rotate_left.c++ \
	N_set.c++ \
	degeneracy.c++ \
	super_triangle.c++ \
	LawsonSwap.c++ \
	vanish_boundary_triangle.c++ \
	delaunay.c++ \
	count_nodes.c++ \
	generate_fN.c++ \
	plotmesh.c++ \
	sortmesh.c++ \
	p2.c++ \
	op.c++ \
	incircle.c++ \
	solver.c++ \
	fscanxyc.c++ \
	printmesh.c++ \
	femesh.c++ 


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
