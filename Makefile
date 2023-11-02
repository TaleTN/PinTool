# Copyright (C) 2023 Theo Niessink <theo@taletn.com>
# This work is free. You can redistribute it and/or modify it under the
# terms of the Do What The Fuck You Want To Public License, Version 2,
# as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

CFLAGS = /O2 /W3 /nologo

all : pintool.exe

pintool.exe : pintool.c
	$(CC) $(CFLAGS) $**

clean :
	@for %i in (pintool.obj pintool.exe) do @if exist %i del %i | echo del %i
