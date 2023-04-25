OBJ=batparse.o getcmd.o memused.o strutils.o utils.o proc.o
GIMPL_PATH=../glib_impl
INCLUDE=-I./ -I${GIMPL_PATH}
LCLUDE=-L./ -L${GIMPL_PATH}
CC=clang
LIB=libmst.a
MAIN=main
FLAGS=-O3 -ggdb

all: $(LIB) $(MAIN) 
$(OBJ):%.o:%.c
	${CC} -c ${FLAGS} $^ ${INCLUDE} -o $@
$(LIB):$(OBJ)
	ar rcs $@ $^
$(MAIN):
	${CC}  $@.c -o $@ ${FLAGS} ${INCLUDE} ${LCLUDE} -lmst -lgimpl
cleanobj:
	rm -rf *.o
clean:
	rm -rf *.o *.a $(MAIN)
