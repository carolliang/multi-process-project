all:
	gcc -o wordc-mp wordc-mp.c wordc-mp.h -lm
gdb:
	gcc -g -o wordc-mp wordc-mp.c wordc-mp.h -lm

clean:
	rm file_part* wordc-mp 	
