include config.mk
OBJ=batparse.o getcmd.o memused.o strutils.o utils.o proc.o
LIB=libmst.a
MAIN=main.c
INSTALL=/usr/bin/st

all: $(LIB) st
install:$(INSTALL)
$(OBJ):%.o:src/%.c
	${CC} -c $^ ${FLAGS} ${INCLUDE} -o src/$@
$(LIB):$(OBJ)
	ar rcs $@ $(patsubst %.o,src/%.o,$^)
st:$(patsubst %.c,src/%.c,$(MAIN))
	${CC}  $^ -o $@  ${FLAGS} ${INCLUDE} ${LCLUDE} -lmst -lgimpl
$(INSTALL):st
	cp $^ $@
cleanobj:
	rm -rf *.o
clean:
	rm -rf src/*.o *.a st
