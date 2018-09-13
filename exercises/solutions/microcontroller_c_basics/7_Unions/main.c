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
	// blue: 0000000 00000000 00000000 11111111
	c.channels.g = 0xF0;
	// green and blue mixed: 00000000 00000000 11110000 11111111
	
	printf("sizeof(union Color): %d byte\n", sizeof(union Color));
	printf("content according to argb: 0x%08x\n", c.argb);
	printf("content according to channels: 0x%02x 0x%02x 0x%02x 0x%02x\n", 
	    c.channels.a, c.channels.r, c.channels.g, c.channels.b);
	printf("addresses of\nargb: %p\nchannels.a: %p\nchannels.r: %p\nchannels.g: %p\nchannels.b:%p\n",
        &c.argb, &c.channels.a,&c.channels.r,&c.channels.g,&c.channels.b);
	
	return 0;
}