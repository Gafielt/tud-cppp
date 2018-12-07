#include "src/dht11.h"

/**
 * GPIO1PIN_P52: The data connector of DHT11 is connected to Port5, Pin2 (located at CN17, Pin 3)
 */
uint8_t readDHT11_s(uint8_t *feuchtigkeit, uint8_t *temperatur) {
  
  Gpio1pin_Put(GPIO1PIN_P52, 1);
  cppp_microDelay(250);
	if (Gpio1pin_Get(GPIO1PIN_P52) == 0) {return 1;}									// Bus not free
  // MCU start signal (>=18ms)
  
  Gpio1pin_InitOut(GPIO1PIN_P52, Gpio1pin_InitVal(0u));
	cppp_microDelay(20000);

  Gpio1pin_InitIn(GPIO1PIN_P52, Gpio1pin_InitPullup(1u));
	uint16_t timeout = 1000;
	while(Gpio1pin_Get(GPIO1PIN_P52) == 1) {if (!timeout--) {return 2;}}				// Wait for DHTís response (20-40us)
	timeout = 1000; 
	while(Gpio1pin_Get(GPIO1PIN_P52) == 0) {if (!timeout--) {return 3;}}				// Response signal (80us)
	timeout = 1000;	
	while(Gpio1pin_Get(GPIO1PIN_P52) == 1) {if (!timeout--) {return 4;}}				// Preparation for sending data (80us)
  timeout = 1000;  
  while(Gpio1pin_Get(GPIO1PIN_P52) == 0) {if (!timeout--) {return 5;}}        
  timeout = 1000;  
  while(Gpio1pin_Get(GPIO1PIN_P52) == 1) {if (!timeout--) {return 6;}}  
	uint8_t dht11_data[5]={0};
  uint8_t i,j = 0;
	for(i=0;i<5;i++)
	{
		uint8_t dht11byte = 0;
		for(j=1;j<=8;j++)
		{
			timeout = 1000;
			while(Gpio1pin_Get(GPIO1PIN_P52) == 0) {if (!timeout--) {return 7;}}		// Start to transmit 1-Bit (50 us)
			cppp_microDelay(30);
			dht11byte <<= 1;
			if (Gpio1pin_Get(GPIO1PIN_P52) == 1)										// Hi > 30us (70 us) -> Bit=1										
			{
				dht11byte |= 1;
				timeout = 1000;
				while(Gpio1pin_Get(GPIO1PIN_P52) == 1) {if (!timeout--) {return 8;}}
			}														// Hi <  30us (26-28 us) -> Bit=0	
		}
		dht11_data[i] = dht11byte;
	}
  
  // Checksum
  if( !(data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) )
	{
		return 9;													
	}	
  
	*feuchtigkeit = dht11_data[0];
	*temperatur = dht11_data[2];
  
	return 0;
} 


void rauminformationen_s(){
      
      setCursor_s(0, 319);
      char freeSpace[] = " ";
      char headlineText[] = "      Umgebungssensoren";
      writeTextln_s(freeSpace);
      writeTextln_s(freeSpace);
      writeTextln_s(freeSpace);
      writeTextln_s(headlineText);
      writeTextln_s(freeSpace);
      
      uint8_t feuchtigkeit, temperatur  = 0;
      uint8_t result = readDHT11_s(&feuchtigkeit, &temperatur);
      
      char temperaturText[] = "      Temperatur (Celsius) : ";
      writeText_s(temperaturText);
      writeNumberOnDisplay_s(&temperatur);
      writeTextln_s("");
      
      char feuchtigkeitText[] = "      Feuchtigkeit (%) : ";
      writeText_s(feuchtigkeitText);
      writeNumberOnDisplay_s(&feuchtigkeit); 
      writeTextln_s("");
      
      cppp_microDelay(50000);
      
}