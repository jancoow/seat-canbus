#ifndef ColorLedMode_h
#define ColorLedMode_h

#include "../LedMode.h"

class ColorLedMode: public LedMode{
  public:
    ColorLedMode(CarLedStrip* car_led_strip): LedMode(car_led_strip){};

    void handleEvent(CarCanbusEvent *event) override {
      if(event->eventType == onVolumeUpPress){
          setNextColor();
          this->car_led_strip->setColor(colors[current_color][0], colors[current_color][1], colors[current_color][2]);
          this->car_led_strip->show();
      }else if(event->eventType == onVolumeDownPress){
          setPreviousColor();
          this->car_led_strip->setColor(colors[current_color][0], colors[current_color][1], colors[current_color][2]);
          this->car_led_strip->show();
      }else if(event->eventType == onTurnLightLeftOn){
          // this->car_led_strip->setLeftDoorColor(255, 165, 0);
          // this->car_led_strip->show();
          animation_running = true;
          left = true;
          step = 0;
      }else if(event->eventType == onTurnLightLeftOff){
          this->car_led_strip->setColor(colors[current_color][0], colors[current_color][1], colors[current_color][2]);
          this->car_led_strip->show();
          animation_running = false;
      }else if(event->eventType == onTurnLightRightOn){
          // this->car_led_strip->setRightDoorColor(255, 165, 0);
          // this->car_led_strip->show();
          left = false;
          animation_running = true;
          step = 0;
      }else if(event->eventType == onTurnLightRightOff){
          this->car_led_strip->setColor(colors[current_color][0], colors[current_color][1], colors[current_color][2]);
          this->car_led_strip->show();
          animation_running = false;
      }else if(event->eventType == onBrakeLightsOn){
          this->car_led_strip->setFrontColor(255, 0, 0);
          this->car_led_strip->show();
      }else if(event->eventType == onBrakeLightsOff){
          this->car_led_strip->setColor(colors[current_color][0], colors[current_color][1], colors[current_color][2]);
          this->car_led_strip->show();
      }else if(event->eventType == onForwardPress){
          this->car_led_strip->setBrightness(this->car_led_strip->getBrightness()+5);
          this->car_led_strip->show();
      }else if(event->eventType == onBackwardsPress){
          this->car_led_strip->setBrightness(this->car_led_strip->getBrightness()-5);
          this->car_led_strip->show();
      }
    };

    void setNextColor(){
      if(current_color == colors_len-1){
        current_color = 0;
      }else{
        current_color+=1;
      }
    }

    void setPreviousColor(){
      if(current_color == 0){
        current_color = colors_len-1;
      }else{
        current_color-=1;
      }
    }

    void onActivate(){
        this->car_led_strip->setColor(colors[current_color][0], colors[current_color][1], colors[current_color][2]);
         this->car_led_strip->show();
    }

    void handleTick(){
        for(int i = number_of_front_leds; i < number_of_leds; i++){
          if((i-number_of_front_leds) * 255 < step*20){
            if(left)
              this->car_led_strip->strip_left.setPixelColor(i-1, 255, 50, 0);
            else
              this->car_led_strip->strip_right.setPixelColor(i, 255, 50, 0);
          }else{
            if(left)
              this->car_led_strip->strip_left.setPixelColor(i-1, (step*20) % 255, 50, 0);
            else
              this->car_led_strip->strip_right.setPixelColor(i, (step*20) % 255, 50, 0);
            break;
          }
        }
        this->car_led_strip->show();
        step+=1;
      }
       
    };

  private:
    uint8_t colors[12][3] = {{5, 180,215}, {200, 50, 0}, {255,0,0}, {0, 255, 0}, {0,0,255}, {0,255,100}, {10,255,255}, {57, 106, 177}, {218, 124, 48}, {62, 150, 81}, {204, 37, 41}, {107, 76, 154}};
    int colors_len = 11;
    int current_color = 0;

    int step = 0;
    bool animation_running = false;
    bool left = false;

};

#endif
