

include config.mk

SRC = ctodo.c essentials.c
OBJ = ${SRC:.c=.o}


all: options ctodo 

options:
	@echo Change in config.mk if needed:
	@echo "Version -> ${VERSION}"
	@echo "CFLAGS = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC = ${CC}"
	@echo "--------------------------"

.c.o:
	${CC} -c -o $@ ${CFLAGS} $< 

ctodo: ${OBJ}
	${CC} -o $@ ${OBJ} ${CFLAGS} ${LDFLAGS}
clean:
	rm ctodo *.o 
