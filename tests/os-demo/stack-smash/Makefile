LDFLAGS = -static-pie
CFLAGS = -Wall -g -fPIE

.PHONY: all clean

all: stack-smash-no-protector stack-smash-protector

stack-smash-no-protector: stack-smash.c
	gcc $(CFLAGS) $(LDFLAGS) -Wall -g -fno-stack-protector -o $@ $^

stack-smash-protector: stack-smash.c
	gcc $(CFLAGS) $(LDFLAGS) -Wall -g -fstack-protector-all -o $@ $^

clean:
	-rm -f stack-smash-protector stack-smash-no-protector
	-rm -f *~
	-rm -f *.o
