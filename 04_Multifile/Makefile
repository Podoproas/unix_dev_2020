GENERATES = README prog prog-a prog-so liboutput_static.a liboutput.so
TRASH = *.o *~ o.* *.txt
CFLAGS = -fPIC
LD_LIBRARY_PATH = . # I do not understand why it is not working and we need -L. in ll 12;15
					# https://docs.oracle.com/cd/E19683-01/816-1386/chapter2-41106/index.html

all: README prog prog-a prog-so
	make clean

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o prog-a

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o prog-so

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

README: prog
	./$< 2> $@

fun.o: outlib.h

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

test: prog prog-a prog-so
	./prog 2> res.txt
	./prog p1 >> res.txt
	./prog p1 p2 p3 >> res.txt

	./prog-a 2> res-a.txt
	./prog-a p1 >> res-a.txt
	./prog-a p1 p2 p3 >> res-a.txt

	$ LD_LIBRARY_PATH=`pwd` ./prog-so 2> res-so.txt
	$ LD_LIBRARY_PATH=`pwd` ./prog-so p1 >> res-so.txt
	$ LD_LIBRARY_PATH=`pwd` ./prog-so p1 p2 p3 >> res-so.txt

	cmp res.txt res-a.txt
	cmp res.txt res-so.txt
	make clean
