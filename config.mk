GIMPL_PATH=../glib_impl
INCLUDE=-I./ -I${GIMPL_PATH}
LCLUDE=-L./ -L${GIMPL_PATH}
FLAGS=-Wno-format-invalid-specifier -O3 -ggdb
CC=clang
