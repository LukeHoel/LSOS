#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define ENTER_KEY_CODE 0x1C

extern void keyboardHandler(void);
extern char readPort(unsigned short port);
extern void writePort(unsigned short port, unsigned char data);
extern void loadIdt(unsigned long *idtptr);

struct IDTEntry{
	unsigned short int offsetLowerBits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char typeAttr;
	unsigned short int offsetHigherBits;
};

struct IDTEntry IDT[IDT_SIZE];

void idtInit(void)
{
	unsigned long keyboardAddress;
	unsigned long idtAddress;
	unsigned long idtPtr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboardAddress = (unsigned long)keyboardHandler; 
	IDT[0x21].offsetLowerBits = keyboardAddress & 0xffff;
	IDT[0x21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[0x21].zero = 0;
	IDT[0x21].typeAttr = 0x8e; /* INTERRUPT_GATE */
	IDT[0x21].offsetHigherBits = (keyboardAddress & 0xffff0000) >> 16;

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	writePort(0x20 , 0x11);
	writePort(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	writePort(0x21 , 0x20);
	writePort(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	writePort(0x21 , 0x00);  
	writePort(0xA1 , 0x00);  

	/* ICW4 - environment info */
	writePort(0x21 , 0x01);
	writePort(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	writePort(0x21 , 0xff);
	writePort(0xA1 , 0xff);

	/* fill the IDT descriptor */
	idtAddress = (unsigned long)IDT ;
	idtPtr[0] = (sizeof (struct IDTEntry) * IDT_SIZE) + ((idtAddress & 0xffff) << 16);
	idtPtr[1] = idtAddress >> 16 ;

	loadIdt(idtPtr);
}
