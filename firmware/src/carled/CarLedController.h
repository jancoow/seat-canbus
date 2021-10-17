#ifndef CarLed_h
#define CarLed_h

#include <Adafruit_NeoPixel.h> 
#include "LedMode.h"
#include "ledmodes/ColorLedMode.h"
#include "CarLedStrip.h"

#define left_neopixel_pin   5
#define right_neopixel_pin  6
#define number_of_leds      34

#define number_of_led_modes 1


class CarLedController{
  public:
    CarLedController(){

    };

    void handleEvent(CarCanbusEvent *event){
        if(event->eventType == onTurnLightLeftOn){
          //set_left_side_led_color(255, 165, 0);
        }else if(event->eventType == onTurnLightLeftOff){
          //set_left_side_led_color(0, 0, 0);
        }else if(event->eventType == onTurnLightRightOn){
          //set_right_side_led_color(255, 165, 0);
        }else if(event->eventType == onTurnLightRightOff){
          //set_right_side_led_color(0, 0, 0);
        }else if(event->eventType == onHazardLightsOn){
          //set_side_led_color(255, 165, 0);
        }else if(event->eventType == onHazardLightsOff){
          //set_side_led_color(0, 0, 0);
        }else if(event->eventType == onLeftDoorOpen){
          //set_left_front_led_color(255, 0, 0);
        }else if(event->eventType == onLeftDoorClose){
          //set_left_front_led_color(0, 0, 0);
        }else if(event->eventType == onLowBeamHeadLightsOn){
          carLedStrip.setBrightness(50);
          carLedStrip.show();
        }else if(event->eventType == onLowBeamHeadLightsOff){
          carLedStrip.setBrightness(100);
          carLedStrip.show();
        }else if(event->eventType == onScrollUpPress){
          setNextMainMode();
        }else if(event->eventType == onScrollDownPress){
          setPreviousMainMode();
        }

        this->ledModes[current_led_mode]->handleEvent(event);
    };
    void tick(){
       this->ledModes[current_led_mode]->handleTick();
    }    
 private:
    CarLedStrip carLedStrip;

    int current_led_mode = 0;
    LedMode* ledModes[number_of_led_modes] = {
      new ColorLedMode(&carLedStrip)
    };


    void setNextMainMode(){
      Serial.println("Going to next mode");
      if(current_led_mode == number_of_led_modes-1){
        current_led_mode = 0;
      }else{
        current_led_mode+=1;
      }
    }

    void setPreviousMainMode(){
      Serial.println("Going to previous mode");
      if(current_led_mode == 0){
        current_led_mode = number_of_led_modes-1;
      }else{
        current_led_mode-=1;
      }
    }


};
#endif
