#include <stdio.h>
#include <stdint.h>

struct Channels { // 1 + 1 + 1 + 1 = 4 Bytes
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
};

union Color {
	uint32_t argb;
	struct Channels channels;
};


int main(void)
{
	union Color c;
	c.argb = 0xFF;
	// blau: 0000000 00000000 00000000 11111111
	c.channels.g = 0xF0;
	// grün und blau: 00000000 00000000 11110000 11111111
	printf("sizeof(Union): %d Bytes\n", sizeof(union Color));
	printf("content according to argb: %x \n", c.argb);
	printf("content according to channels: %x %x %x %x  \n", c.channels.b, c.channels.g, c.channels.r, c.channels.a);
	printf("address of argb: %u \n",&c.argb);
	printf("addres of channels.a: %u \n channels.r: %u \n channels.g: %u \n channels.b:%u \n ",&c.channels.a,&c.channels.r,&c.channels.g,&c.channels.b);
	
	return 0;
}