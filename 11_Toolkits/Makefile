all: a.out

a.out:
		cc `pkg-config --cflags glib-2.0` main.c -o prog `pkg-config --libs glib-2.0`

clean:
		rm -f prog