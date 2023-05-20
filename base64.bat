REM CommandInterpreter: $(COMSPEC)
erase base64.obj

nasmw -f obj -o base64.obj base64.asm

pause
