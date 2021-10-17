#ifndef LedMode_h
#define LedMode_h

#include "CarLedStrip.h"

class LedMode{
  public:
    virtual void handleEvent(CarCanbusEvent *event);
    virtual void handleTick();
  protected:
     LedMode(CarLedStrip* car_led_strip): car_led_strip(car_led_strip){};
     CarLedStrip* car_led_strip;
};

#endif
