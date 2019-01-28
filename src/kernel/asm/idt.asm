global readPort
global writePort
global loadIdt
global keyboardHandlerWrapper
 
extern keyboardHandler

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

keyboardHandlerWrapper:                 
	call    keyboardHandler
	iretd

section .bss
resb 64000	;64KB for stack
stackSpace:
