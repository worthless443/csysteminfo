OBJ=batparse.o getcmd.o memused.o strutils.o
INCLUDE=-I./ -I../glib_impl
LCLUDE=-L./ 
CC=gcc
LIB=libmst.a
MAIN=main

all: $(LIB) $(MAIN) 
$(OBJ):%.o:%.c
	${CC} -c $^ ${INCLUDE} -o $@
$(LIB):$(OBJ)
	ar rcs $@ $^
$(MAIN):
	${CC}  $@.c -o $@  ${INCLUDE} ${LCLUDE} -lmst
cleanobj:
	rm -rf *.o
clean:
	rm -rf *.o *.a $(MAIN)
