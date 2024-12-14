CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -fPIE -g
LDFLAGS = -static-pie
LDLIBS = -lpthread

.PHONY: all clean

all: producer_consumer

producer_consumer: producer_consumer.o ring_buffer.o

producer_consumer.o: producer_consumer.c ../utils/utils.h

ring_buffer.o: ring_buffer.c ../utils/utils.h

clean:
	-rm -f *~
	-rm -f ring_buffer.o producer_consumer.o producer_consumer
