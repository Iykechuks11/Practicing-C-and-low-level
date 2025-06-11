all: note bitwise flag uid notetaker notesearch

note: 0x0_simplenote.c
	cc 0x0_simplenote.c -o build/simplenote.o

bitwise: 0x1_bitwise.c
	cc 0x1_bitwise.c -o build/bitwise.o

flag: 0x2_fcntl_flag.c
	cc 0x2_fcntl_flag.c -o build/fcntl_flag.o

uid: 0x3_uid_demo.c
	cc 0x3_uid_demo.c -o build/uid_demo.o

notetaker: 0x4_notetaker.c
	cc 0x4_notetaker.c -o build/notetaker.o

notesearch: 0x5_notesearch.c
	cc 0x5_notesearch.c -o build/notesearch.o

clean:
	rm -f build/*.o