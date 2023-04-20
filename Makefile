include config.mk
OBJ=batparse.o getcmd.o memused.o strutils.o
LIB=libmst.a
MAIN=main.c
INSTALL=/usr/bin/st

all: $(LIB) st
install:$(INSTALL)
$(OBJ):%.o:%.c
	${CC} -c $^ ${INCLUDE} -o $@
$(LIB):$(OBJ)
	ar rcs $@ $^
st:$(MAIN)
	${CC}  $^ -o $@  ${INCLUDE} ${LCLUDE} -lmst -lgimpl
$(INSTALL):st
	cp $^ $@
cleanobj:
	rm -rf *.o
clean:
	rm -rf *.o *.a st
