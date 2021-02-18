TRASH =  *.so
name1 = good_file
name2 = bad_file_FIX


all: wrapper.so

wrapper.so: wrapper.c
	gcc wrapper.c -shared -fPIC -ldl -o wrapper.so


test: wrapper.so
	touch $(name1)
	touch $(name2)

	LD_PRELOAD=./wrapper.so rm $(name1)
	LD_PRELOAD=./wrapper.so rm $(name2) || true

	test -f $(name2)
	rm $(name2)

	echo "PASSED"

clean:
	rm -f $(TRASH) $(name1) $(name2)
