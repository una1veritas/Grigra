
COMPILER = g++
CPPOPTS = -O3 -g -Wall

INCLUDE_PATH = ./include
OBJ_PATH = ./obj
SRC_PATH = ./src
BIN_PATH = ./bin

TARGET_EXECUTABLE = ${BIN_PATH}/layout.exe
TARGET_STATICLIBRARY = ${BIN_PATH}/gridlayout.lib

MAIN = $(OBJ_PATH)/main.o
OBJS = point table layout reader printer

OBLIST = $(addprefix ${OBJ_PATH}/, ${OBJS:=.o})
INLIST = -I${INCLUDE_PATH}

.PHONY : all
all : ${TARGET_EXECUTABLE} ${TARGET_STATICLIBRARY}
	echo success!

${TARGET_EXECUTABLE} : ${MAIN} ${OBLIST}
	${COMPILER} ${CPPOPTS} $^ -o $@ ${INLIST}

${TARGET_STATICLIBRARY} : ${OBLIST}
	${COMPILER} ${CPPOPTS} $^ -c -o $@ ${INLIST}

obj/%.o : src/%.cpp
	${COMPILER} ${CPPOPTS} $^ -c -o $@ ${INLIST}

.PHONY : clean
clean :
	\rm -f ./bin/* ./obj/*.o

