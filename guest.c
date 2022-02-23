#include <stddef.h>
#include <stdint.h>

// static void outb(uint16_t port, uint8_t value) {
// 	asm("outb %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
// }

static inline void outb(uint16_t port, uint32_t value) {
  asm("out %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
}

static inline uint32_t inb(uint16_t port) {
  uint32_t ret;
  asm("in %1, %0" : "=a"(ret) : "Nd"(port) : "memory" );
  return ret;
}

void printVal(uint32_t val){
	outb(0xE1, val);
}

uint32_t getNumExits(){
	uint32_t numExits;
	numExits = inb(0xE0);
	return numExits;
}

void display(const char *str){
	outb(0xE2, (uintptr_t)str);
}

void
__attribute__((noreturn))
__attribute__((section(".start")))
_start(void) {
	//const char *p;

	// for (p = "Hello, world!\n"; *p; ++p)
	// 	outb(0xE9, *p);

	uint32_t numExits = getNumExits();
	printVal(numExits);
	const char *q;
	q = "Hello, world!\n";
	display(q);
	printVal(numExits);



	*(long *) 0x400 = 42;
	for (;;)
		asm("hlt" : /* empty */ : "a" (42) : "memory");
}
