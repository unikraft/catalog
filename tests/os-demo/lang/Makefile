LDFLAGS = -static-pie
.PHONY: all

all: MultithreadingTest.class

MultithreadingTest.class: MultithreadingTest.java
	javac $<

clean:
	-rm -f *~
	-rm -f MultithreadingTest.class MultithreadingDemo.class
