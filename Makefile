CFLAGS = /O2 /W3 /nologo

all : pintool.exe

pintool.exe : pintool.c
	$(CC) $(CFLAGS) $**

clean :
	@for %i in (pintool.obj pintool.exe) do @if exist %i del %i | echo del %i
