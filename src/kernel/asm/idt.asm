global readPort
global writePort
global loadIdt
global keyboardHandler
 
extern keyboardHandlerMain

readPort:
	mov edx, [esp + 4]
	in al, dx	
	ret

writePort:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

loadIdt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

keyboardHandler:                 
	call    keyboardHandlerMain
	iretd

section .bss
resb 64000	;64KB for stack
stackSpace:
