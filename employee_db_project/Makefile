TARGET = bin/program
SRC = ${wildcard src/*.c}
OBJ = ${patsubst src/%.c, obj/%.o, ${SRC}}

run: clean default
	./${TARGET} -f db_file.db -n
	./${TARGET} -f db_file.db -a "yaser,hargeisa,21"

default: ${TARGET}

clean:
	rm -f bin/*
	rm -f obj/*.o
	rm -f *.db
${TARGET}: ${OBJ}
	gcc -o $@ $^
obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinclude -Wpedantic