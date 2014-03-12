main: recurse.c process.c process.h sl.h sorted-list.c sorted-list.h uthash.h
	rm aux.txt
	clear
	gcc -o main recurse.c process.c process.h sl.h sorted-list.c sorted-list.h uthash.h
	./main index.txt sample
	rm main

debug: recurse.c process.c process.h sl.h sorted-list.c sorted-list.h uthash.h
	clear
	gcc -g recurse.c process.c process.h sl.h sorted-list.c sorted-list.h uthash.h
	gdb a.out
	
clean: 
	rm main

	
