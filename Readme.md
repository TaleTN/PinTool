# PinTool

PinTool is a PIN Input Typing Assistant&trade; (PITA), that automates typing
your PIN when code-signing a Windows binary using a
[Hardware Security Module](https://en.wikipedia.org/wiki/Hardware_security_module)
(HSM), e.g. a [YubiKey](https://en.wikipedia.org/wiki/YubiKey).

## How to build

1. Open the Command Prompt for VS (Visual Studio).

2. Run the Program Maintenance Utility (NMAKE) to build PinTool:

    `nmake`

3. Done! There wasn't even time to get a coffee or a tea...

## How to use

When code-signing a binary add PinTool just before SignTool, e.g.:

```
start pintool.exe 123456
signtool sign /v /n "My Company" /a /fd sha256 /tr "http://ts.ssl.com" /td sha256 my_binary.exe
```

Replace `123456` with your PIN, or maybe with an environment variable
holding your PIN.

This will start PinTool in the background, and then immediately return and
run SignTool. As soon as the Windows Security dialog is detected by PinTool,
it will start "typing" your PIN and then hit the enter key, after which
PinTool will terminate.

If your automated build script calls SignTool multiple times, then you
should add PinTool before each SignTool call.

## License

Copyright &copy; 2023 Theo Niessink &lt;theo@taletn.com&gt;  
This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
