#include "dht11.h"

uint8_t readDHT11(uint8_t *feuchtigkeit, uint8_t *temperatur) {
  Gpio1pin_Put(GPIO1PIN_P52, 1);
  cppp_microDelay(250);
	if (Gpio1pin_Get(GPIO1PIN_P52) == 0) {return 1;}									// Bus not free
	          // MCU start signal (>=18MS
  

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
  
  // Implement here a for loop from 0 ... 4
    // Implement here a for loop from 0 ... 7
  
    // check if received data is a 1 or a 0 bit
    // 1 bit: HIGH signal more than 30µs
    // 0 bit: HIGH signal less than 30µs
  
  // check if checksum is correct
  //if (dht11_data[0]+dht11_data[1]+dht11_data[2]+dht11_data[3] != dht11_data[4])
 
  // return humidity and temperature

	return 0;
} 


void rauminformationen(){
      setCursor(0,319);
      char freeSpace[] = " ";
      char headlineText[] = "      Umgebungssensoren";
      writeTextln(freeSpace);
      writeTextln(freeSpace);
      writeTextln(freeSpace);
      writeTextln(headlineText);
      writeTextln(freeSpace);
      
      uint8_t feuchtigkeit, temperatur  = 0;
      
      // fetch here DHT11 data

            
      char temperaturText[] = "      Temperatur (Celsius) : ";
      writeText(temperaturText);
      //  print here temperature from DHT11
      
      char feuchtigkeitText[] = "      Feuchtigkeit (%) : ";
      writeText(feuchtigkeitText);
      //  print here humidity from DHT11
      
      cppp_microDelay(50000);
}