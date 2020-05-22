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
	fscanxyc.c++ \
	printmesh.c++ \
	femesh.c++ \
	main.c++


OBJS = $(SRCS:.c++=.o)
.SUFFIXES: .c++ .o

CPPFLAGS = -Wall
LDFLAGS = 

.PHONY: all clean

all: $(PROG)

$(PROG) : $(OBJS)
	c++ $(OBJS) -o $@ $(LDFLAGS)

.c++.o:
	c++ $(CPPFLAGS) -c $< 

obj: $(OBJS)
	ar cr lib/libxmesh.a $(OBJS)
	rm *.o

clean :
	rm -f $(OBJS) $(PROG) lib/libxmesh.a 


test: $(PROG)
	./femesh ../kanto.xyc -o ../tmp.mesh
	diff ../kanto.mesh ../tmp.mesh
	./femesh ../pt.xyc -o ../tmp.mesh
	diff ../pt.mesh ../tmp.mesh
	./femesh ../square.xyc -o ../tmp.mesh
	diff ../square.mesh ../tmp.mesh
	rm -f ../tmp.mesh
