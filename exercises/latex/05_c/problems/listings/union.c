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
	
	return 0;
}