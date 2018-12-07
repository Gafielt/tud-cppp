timeout = 1000
while(Gpio1pin_Get(GPIO1PIN_P52) == 0) {
  if (!timeout--) {
    return 0;
  }
}
