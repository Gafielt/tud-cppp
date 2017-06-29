/**
 *  This code is based on:  https://github.com/adafruit/Adafruit-GFX-Library &  https://github.com/adafruit/TFTLCD-Library
 *  The code is converted by Puria Izady for the Cypress FM4  microcontroller
 */

#include "lcd.h"


/** 
 *  Delays the programm 
 *  @param length of delay
 */
void  delay(int n){
    volatile unsigned long u32Delay;
    for(u32Delay = n*450; u32Delay > 0; u32Delay--);
}

/**
 *  Toggles between LCD_WR_ACTIVE and LCD_WRITE_IDLE.
 */
void writeStrobe(){
    LCD_WR = 0u;
    LCD_WR = 1u;
}

/**
 *  Writes 8 Bits parallel on the Data-Pins 0-7.
 *  @param char d - the 8 bit data
 */
void write8(char d) {
    LCD_DATA = d;
    writeStrobe();
}

/**
 *  Writes 32 Bits 4 times serial on the parallel Data-Pins 0-7.
 *  @param long d - the 32 bit data
 */
void write32(char r, long d) {
    LCD_CS = 0u;    // LCD_CS_ACTIVE
    LCD_CD = 0u;
    write8(r);
    LCD_CD = 1u;
    write8(d >> 24);
    write8(d >> 16);
    write8(d >> 8);
    write8(d);
    LCD_CS = 1u;    // LCD_CS_IDLE
}

/**
 *  Set Value of the TFT 8-bit registers aH and aL with the low and high parts of the 16 bit value d.
 *
 */
void writeRegisterPair(char aH, char aL, int d) {
    char hi = (d) >> 8, lo = (d);
    LCD_CD = 0u; write8(aH); LCD_CD = 1u; write8(hi);
    LCD_CD = 0u; write8(aL); LCD_CD = 1u; write8(lo);
}

/**
  *    Writes command and data on 8-Data pins.
  */
void writeRegister8(char a, char d) {
    LCD_CD = 0u;
    write8(a);
    LCD_CD = 1u;
    write8(d);
}

 /**
 *  Sets the Window of coordinates, that are going to be manipulated by a method.
 */
void setAddrWindow(int x1, int y1, int x2, int y2){
    LCD_CS = 0u;
    unsigned long t;
    
    t = x1;
    t <<= 16;
    t |= x2;
    write32(ILI9341_PAGEADDRSET, t);  // HX8357D uses same registers!    
    t = y1;
    t <<= 16;
    t |= y2;
    write32(ILI9341_COLADDRSET, t); // HX8357D uses same registers!                 
    LCD_CS = 1u;
}

/**
 * Initialization of the direction and start value of 8 data and 5 control pins
 */
void init(){
    // Set LCD Data Pins orientation to output
    LCD_DATA_IO  = 0xFF; // Direction: Output

    
    // Set all LCD Data Pins to LOW
    LCD_DATA = 0xFF;  // LCD_D0 => HIGH

    
    // SET ANALOG PINS TO DIGITAL
    bFM4_GPIO_ADE_AN00 = 0;
    bFM4_GPIO_ADE_AN01 = 0;
    bFM4_GPIO_ADE_AN02 = 0;
    bFM4_GPIO_ADE_AN03 = 0;
    bFM4_GPIO_ADE_AN04 = 0;
    bFM4_GPIO_ADE_AN05 = 0;
    bFM4_GPIO_ADE_AN06 = 0;
    bFM4_GPIO_ADE_AN07 = 0;
    
    // SET ANALOG PINS
    bFM4_GPIO_ADE_AN11 = 1u;
    bFM4_GPIO_ADE_AN12 = 1u;
    bFM4_GPIO_ADE_AN13 = 1u;
    bFM4_GPIO_ADE_AN16 = 1u;
    bFM4_GPIO_ADE_AN19 = 1u;
    bFM4_GPIO_ADE_AN23 = 1u;
    
    JS1_X_IO = 1u;
    JS1_Y_IO = 1u;
    JS2_X_IO = 1u;
    JS2_Y_IO = 1u;
    
    // SET LCD CONTROL PINS TO OUTPUT MODE
    LCD_RD_IO = 1u;
    LCD_WR_IO = 1u;
    LCD_CD_IO = 1u;
    LCD_CS_IO = 1u;
    LCD_RS_IO = 1u;
    
    // SET ALL LCD CONTROL PINS TO HIGH
    LCD_RD = 1u;
    LCD_WR = 1u;
    LCD_CD = 1u;
    LCD_CS = 1u;
    LCD_RS = 1u;
    
    //DHT11_SIGNAL_OUT = 1u;
    //
    Gpio1pin_InitIn(GPIO1PIN_PF7, Gpio1pin_InitPullup(1u));
    
}

/**
 *  Resets the Display
 */
void reset(){
    volatile unsigned long u32Delay;
    volatile unsigned long i;
    LCD_CS = 1u;    //LCD_CS_IDLE
    //  CD_DATA;
    LCD_WR = 1u;    // LCD_WR_IDLE
    LCD_RD = 1u;    // LCD_RD_IDLE
    
    LCD_RS = 0u;
    for(u32Delay = 1200000; u32Delay > 0; u32Delay--);    //delay(2);
    LCD_RS = 1u;
    
    // Data transfer sync
    LCD_CS = 0u;
    LCD_CD = 0u;
    write8(0x00);               // NOP COMMAND
    for(i=0; i<3; i++) {
        writeStrobe();    // Three extra 0x00s  // WR_STROBE = { LCD_WR = 0u; LCD_WR = 1u; }
    }
    LCD_CS = 1u;
}

/**
 *  Runs the configuration methods of the LCD-Controller
 */
void setupLCD() {
    static const long HX8357D_regValues[] = {
        HX8357_SWRESET, 0,
        HX8357D_SETC, 3, 0xFF, 0x83, 0x57,
        TFTLCD_DELAY, 250,
        HX8357_SETRGB, 4, 0x00, 0x00, 0x06, 0x06,
        HX8357D_SETCOM, 1, 0x25,  // -1.52V
        HX8357_SETOSC, 1, 0x68,  // Normal mode 70Hz, Idle mode 55 Hz
        HX8357_SETPANEL, 1, 0x05,  // BGR, Gate direction swapped
        HX8357_SETPWR1, 6, 0x00, 0x15, 0x1C, 0x1C, 0x83, 0xAA,
        HX8357D_SETSTBA, 6, 0x50, 0x50, 0x01, 0x3C, 0x1E, 0x08,
        // MEME GAMMA HERE
        HX8357D_SETCYC, 7, 0x02, 0x40, 0x00, 0x2A, 0x2A, 0x0D, 0x78,
        HX8357_COLMOD, 1, 0x55,
        HX8357_MADCTL, 1, 0xC0,
        HX8357_TEON, 1, 0x00,
        HX8357_TEARLINE, 2, 0x00, 0x02,
        HX8357_SLPOUT, 0,
        TFTLCD_DELAY, 150,
        HX8357_DISPON, 0,
        TFTLCD_DELAY, 50,
    };
    volatile unsigned long u32Delay;
    volatile unsigned long i = 0;
    reset();
    delay(200);
    
    LCD_CS = 0u; // LCD_CS_ACTIVE
    
    
    while(i < (sizeof(HX8357D_regValues) / (sizeof(HX8357D_regValues[0])) ) ) {
        volatile unsigned long r = HX8357D_regValues[i++];
        volatile unsigned long len = HX8357D_regValues[i++];
        if(r == TFTLCD_DELAY) {
            delay(len);
        } else {
            LCD_CS = 0u;    // LCD_CS_ACTIVE
            LCD_CD = 0u;
            write8(r);
            LCD_CD = 1u;
            volatile unsigned long d;
            for (d=0; d<len; d++) {
                volatile unsigned long x = HX8357D_regValues[i++];
                write8(x);
            }
            LCD_CS = 1u;    // LCD_CS_IDLE
        }
    }
    return;
}

/**
 *  Kind of a reset for setAddrWindow().
 *
 */
void setLR(void) {
    LCD_CS = 0u;
    writeRegisterPair(HX8347G_COLADDREND_HI, HX8347G_COLADDREND_LO, 480  - 1);    
    writeRegisterPair(HX8347G_ROWADDREND_HI, HX8347G_ROWADDREND_LO, 320 - 1);     
    LCD_CS = 1u;
}

/**
 *  Floods the GRAM len-times. 
 *  @author Puria Izady
 */
void flood(int color, long len){
    volatile unsigned int blocks;
    volatile unsigned char  i, hi = color >> 8,
    lo = color;
    
    LCD_CS = 0u;
    LCD_CD = 0u;
    write8(HX8357_RAMWR);
    
    
    // Write first pixel normally, decrement counter by 1
    LCD_CD = 1u;;
    write8(hi);
    write8(lo);
    len--;
    
    blocks = (volatile unsigned int) (len / 64); // 64 pixels/block
    if(hi == lo) {
        // High and low bytes are identical.  Leave prior data
        // on the port(s) and just toggle the write strobe.
        while(blocks--) {
            i = 16; // 64 pixels/block / 4 pixels/pass
            do {
                writeStrobe(); writeStrobe(); writeStrobe(); writeStrobe(); // 2 bytes/pixel
                writeStrobe(); writeStrobe(); writeStrobe(); writeStrobe(); // x 4 pixels
            } while(--i);
        }
        // Fill any remaining pixels (1 to 64)
        for(i = 63; i--; ) {
            writeStrobe();
            writeStrobe();
        }
    } else {
        while(blocks--) {
            i = 16; // 64 pixels/block / 4 pixels/pass
            do {
                write8(hi); write8(lo); write8(hi); write8(lo);
                write8(hi); write8(lo); write8(hi); write8(lo);
            } while(--i);
        }
        for(i = 63; i--; ) {
            write8(hi);
            write8(lo);
        }
    }
    LCD_CS = 1u;
    
}



