timeout = 1000
while(Gpio1pin_Get(GPIO1PIN_PF7) == 0) {if (!timeout--) {return 0;}}
