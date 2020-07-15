#ifndef ColorLedMode_h
#define ColorLedMode_h

#include "../LedMode.h"
#define number_of_colors 10

class ColorLedMode: public LedMode{
  int colors[number_of_colors][3] = {{255,0,0}, {0, 255, 0}, {0,0,255}, {0,255,100}, {10,255,255}, {57, 106, 177}, {218, 124, 48}, {62, 150, 81}, {204, 37, 41}, {107, 76, 154}};
  int color_index = 0;

  public:
    void handleEvent(CarCanbusEvent *event, Adafruit_NeoPixel *strip_left, Adafruit_NeoPixel *strip_right){
      if(event->eventType == onVolumeUpPress){
        color_index++;
        if(color_index > number_of_colors)
           color_index = 0;
        this->set_whole_led_color(strip_left, strip_right, colors[color_index][0], colors[color_index][1], colors[color_index][2]);
      }else if(event->eventType == onVolumeDownPress){
        color_index--;
        if(color_index < 0)
           color_index = number_of_colors;
        this->set_whole_led_color(strip_left, strip_right, colors[color_index][0], colors[color_index][1], colors[color_index][2]);
      }
    };
    void handleTick(){

    };
  private:

    void set_whole_led_color(Adafruit_NeoPixel *strip_left, Adafruit_NeoPixel *strip_right, int r, int g, int b){
      for(int i = 0; i < 34; i++){
        strip_left->setPixelColor(i, r, g, b);
        strip_right->setPixelColor(i, r, g, b);
     }
    }

};

#endif
