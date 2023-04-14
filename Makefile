include config.mk
OBJ=batparse.o getcmd.o memused.o strutils.o
LIB=libmst.a
MAIN=main.c

all: $(LIB) st
$(OBJ):%.o:%.c
	${CC} -c $^ ${INCLUDE} -o $@
$(LIB):$(OBJ)
	ar rcs $@ $^
st:$(MAIN)
	${CC}  $^ -o $@  ${INCLUDE} ${LCLUDE} -lmst -lgimpl
cleanobj:
	rm -rf *.o
clean:
	rm -rf *.o *.a st
