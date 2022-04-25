#ifndef CarLedStrip_h
#define CarLedStrip_h

#include <Adafruit_NeoPixel.h> 


#define left_neopixel_pin   5
#define right_neopixel_pin  6
#define number_of_front_leds 15
#define number_of_leds      34



class CarLedStrip{
  public:
    CarLedStrip(){
      this->strip_left.begin();  
      this->strip_right.begin();
    };

    void setLeftFrontColor(uint8_t r, uint8_t g, uint8_t b){
        for(uint8_t i = 0; i < number_of_front_leds; i++){
            this->strip_left.setPixelColor(i, r, g, b);
        }
    }

    void setRightFrontColor(uint8_t r, uint8_t g, uint8_t b){
        for(uint8_t i = 0; i < number_of_front_leds; i++){
            this->strip_right.setPixelColor(i, r, g, b);
        }
    }

    void setLeftDoorColor(uint8_t r, uint8_t g, uint8_t b){
        for(uint8_t i = number_of_front_leds; i < number_of_leds; i++){
            this->strip_left.setPixelColor(i, r, g, b);
        }
    }

    void setRightDoorColor(uint8_t r, uint8_t g, uint8_t b){
        for(uint8_t i = number_of_front_leds; i < number_of_leds; i++){
            this->strip_right.setPixelColor(i, r, g, b);
        }
    }

    void setFrontColor(uint8_t r, uint8_t g, uint8_t b){
        for(uint8_t i = 0; i < number_of_front_leds; i++){
            this->strip_left.setPixelColor(i, r, g, b);
            this->strip_right.setPixelColor(i, r, g, b);
        }
    }

    void setDoorColor(uint8_t r, uint8_t g, uint8_t b){
        for(uint8_t i = number_of_front_leds; i < number_of_leds; i++){
            this->strip_left.setPixelColor(i, r, g, b);
            this->strip_right.setPixelColor(i, r, g, b);
        }
    }

    void setColor(uint8_t r, uint8_t g, uint8_t b){
        for(uint8_t i = 0; i < number_of_leds; i++){
            this->strip_left.setPixelColor(i, r, g, b);
            this->strip_right.setPixelColor(i, r, g, b);
        }    
    }

    void setBrightness(uint8_t brightness){
        this->brightness = brightness;
        this->strip_left.setBrightness(brightness);
        this->strip_right.setBrightness(brightness);
    }

    uint8_t getBrightness(){
        return this->brightness;
    }

    void show(){
        this->strip_left.show();
        this->strip_right.show();      
    }

    Adafruit_NeoPixel strip_left = Adafruit_NeoPixel(number_of_leds, left_neopixel_pin, NEO_GRB + NEO_KHZ800);
    Adafruit_NeoPixel strip_right = Adafruit_NeoPixel(number_of_leds, right_neopixel_pin, NEO_GRB + NEO_KHZ800);

    uint8_t brightness;
};
#endif
