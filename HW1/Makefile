include ../Make.defines

PROGS =	myserver myclient test_main test_client \

all:	${PROGS}

myclient:	myclient.o
		${CC} ${CFLAGS} -o $@ myclient.o ${LIBS}

myserver:	myserver.o
		${CC} ${CFLAGS} -o $@ myserver.o ${LIBS}

test_main:	test_main.o
		${CC} ${CFLAGS} -o $@ test_main.o ${LIBS}

test_client: test_client.o
		${CC} ${CFLAGS} -o $@ test_client.o ${LIBS}


clean:
		rm -f ${PROGS} ${CLEANFILES}
