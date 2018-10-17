README

-Open the command line 


-Go to the folder where is located all the downloaded files.
	
	command: cd /..../LOCATION


-Compile all programs using makefile
	
	command: make

-Compile one program using makefile
	
	command: make "FILENAME"


-Run the program
	
	command: ./FILENAME.o

-Clean .o files
	
	command: make clean

Managing Memory
	
	UNIX-style operating systems have had a very clean approach to managing memory, which Linux, because it implements the X/Open specification, has inherited. Linux provides applications with a clean view of a huge directly addressable memory space. Additionally, it provides protection so that different applications are protected from each other, and it allows applications to apparently access more memory than is physically present in the
machine

Allocating Memory
	
	Malloc command helps for allocating physical memory.

Available memory

	There is a limit of physical memory addresses and space
	In program 3...the program has allocated, and accessed, more memory than this author physically has in his machine at the time of writing.

Abusing memory
	
	Suppose you try to do “bad” things with memory. In this exercise, you allocate some memory and then attempt to write past the end. In program 4... the Linux memory management system has protected the rest of the system from this abuse of memory. To ensure that one badly behaved program (this one) can’t damage any other programs, Linux has terminated it.
	
Null Pointer
	
	Unlike MS-DOS, but more like newer flavors of Windows, modern Linux systems are very protective about writing or reading from the address referred to by a null pointer, although the actual behavior is implementation-specific.

Freeing memory

	Linux memory management system is quite capable of reliably ensuring that memory is returned to the system when a program ends. However, most programs don’t simply want to allocate some memory, use it for a short period, and then exit. A much more common use is dynamically using memory as required.
	Free command helps freeing memory






