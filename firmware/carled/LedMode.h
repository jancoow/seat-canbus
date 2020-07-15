#ifndef LedMode_h
#define LedMode_h

class LedMode{
  public:
    virtual void handleEvent(CarCanbusEvent *event, Adafruit_NeoPixel *strip_left, Adafruit_NeoPixel *strip_right){};
    virtual void handleTick(){};
  protected:
     LedMode(){};
};

#endif
