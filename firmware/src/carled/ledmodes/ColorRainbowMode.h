#ifndef ColorFadeMode_h
#define ColorFadeMode_h

#include "../LedMode.h"

class ColorRainbowMode: public LedMode{
  public:
    ColorRainbowMode(CarLedStrip* car_led_strip): LedMode(car_led_strip){};

    void handleEvent(CarCanbusEvent *event) override {
      if(event->eventType == onVolumeUpPress){
        if(speed != 2)
                speed += 0.05;
      }else if(event->eventType == onVolumeDownPress){

                if(speed != 0.05)
          speed -= 0.05;
      }else if(event->eventType == onTurnLightLeftOn){
          // this->car_led_strip->setLeftDoorColor(255, 165, 0);
          // this->car_led_strip->show();
          animation_running = true;
          left = true;
          step = 0;
      }else if(event->eventType == onTurnLightLeftOff){
          animation_running = false;
      }else if(event->eventType == onTurnLightRightOn){
          // this->car_led_strip->setRightDoorColor(255, 165, 0);
          // this->car_led_strip->show();
          left = false;
          animation_running = true;
          step = 0;
      }else if(event->eventType == onTurnLightRightOff){
          animation_running = false;
      }


    };

    void onActivate(){
    }

    void handleTick(){
      if(j == 256){
        j = 0;
      }
      for(int i=0; i< number_of_leds; i++) {
        c=Wheel(((i * 256 / number_of_leds) + (int)j) & 255);
        this->car_led_strip->strip_left.setPixelColor(i, *c, *(c+1), *(c+2));
        this->car_led_strip->strip_right.setPixelColor(i, *c, *(c+1), *(c+2));
      }
      j+= speed;

      if(animation_running){
        Adafruit_NeoPixel *strip;
        if(left)
          strip = &this->car_led_strip->strip_left;
        else
          strip = &this->car_led_strip->strip_right;
        
        if(step == 20000){
          animation_running = false;
          return;
        }
        for(int i = number_of_front_leds; i < number_of_leds; i++){
          if((i-number_of_front_leds) * 255 < step*20){
            strip->setPixelColor(i, 255, 50, 0);
          }else{
            strip->setPixelColor(i, (step*20) % 255, 50, 0);
            break;
          }
        }
        step+=1;
      }
              this->car_led_strip->show();

       
    };


    byte * Wheel(byte WheelPos) {
      static byte c[3];
    
      if(WheelPos < 85) {
      c[0]=WheelPos * 3;
      c[1]=255 - WheelPos * 3;
      c[2]=0;
      } else if(WheelPos < 170) {
      WheelPos -= 85;
      c[0]=255 - WheelPos * 3;
      c[1]=0;
      c[2]=WheelPos * 3;
      } else {
      WheelPos -= 170;
      c[0]=0;
      c[1]=WheelPos * 3;
      c[2]=255 - WheelPos * 3;
      }

      return c;
    }
  private:
  byte *c;
    float speed = 0.1;
    int step = 0;
    float j = 0;
    bool animation_running = false;
    bool left = false;

};

#endif
