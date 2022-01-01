CFLAGS = -Wall -Wextra -pedantic -g
CPPFLAGS = -I./inc/
EXEC = ./bin/
OBJS_TRIVIAL = ./obj/image.o ./obj/table.o ./obj/trivial.o
OBJS_KDARBRE = ./obj/image.o ./obj/table.o ./obj/kdarbre.o
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/
BIN_PATH = ./bin/


all: trivial.bin main.bin kdarbre.bin


trivial.bin: ${OBJS_TRIVIAL}
	gcc $^ -o ${BIN_PATH}$@ 

kdarbre.bin: ${OBJS_KDARBRE}
	gcc $^ -o ${BIN_PATH}$@ 

main.bin: ./obj/main.o  ./obj/image.o ./obj/table.o
	gcc $^ -o ${BIN_PATH}$@  
 
${OBJ_PATH}trivial.o: ${SRC_PATH}trivial.c 
	gcc -c $< -o $@ ${CPPFLAGS}



${OBJ_PATH}main.o: ${SRC_PATH}main.c 
	gcc -c $< -o $@ ${CPPFLAGS}


${OBJ_PATH}table.o: ${SRC_PATH}table.c
	gcc -c $< -o $@ ${CPPFLAGS}
 
${OBJ_PATH}image.o: ./MODULE_IMAGE/image.c
	gcc -c $< -o $@ ${CPPFLAGS}
 
${OBJ_PATH}kdarbre.o: ${SRC_PATH}kdarbre.c 
	gcc -c $< -o $@ ${CPPFLAGS}



