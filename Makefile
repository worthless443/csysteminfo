include config.mk
OBJ=batparse.o getcmd.o memused.o strutils.o utils.o proc.o
LIB=libmst.a
MAIN=main.c
INSTALL=/usr/bin/st

all: $(LIB) st
install:$(INSTALL)
$(OBJ):%.o:%.c
	${CC} -c $^ ${FLAGS} ${INCLUDE} -o $@
$(LIB):$(OBJ)
	ar rcs $@ $^
st:$(MAIN)
	${CC}  $^ -o $@  ${FLAGS} ${INCLUDE} ${LCLUDE} -lmst -lgimpl
$(INSTALL):st
	cp $^ $@
cleanobj:
	rm -rf *.o
clean:
	rm -rf *.o *.a st
