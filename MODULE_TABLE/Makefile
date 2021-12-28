CFLAGS = -Wall -Wextra -pedantic -g
CPPFLAGS = -I./inc/
EXEC = ./bin/
OBJS_SIEVE = ./obj/main.o ./obj/image.o ./obj/table.o 

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/
BIN_PATH = ./bin/


all: main.bin


main.bin: ${OBJS_SIEVE}
	gcc $^ -o ${BIN_PATH}$@ 


${OBJ_PATH}main.o: ${SRC_PATH}main.c 
	gcc -c $< -o $@ ${CPPFLAGS}


${OBJ_PATH}table.o: ${SRC_PATH}table.c
	gcc -c $< -o $@ ${CPPFLAGS}

