#include <Adafruit_NeoPixel.h>
#include "CarCanbus.h"

#define sig 2
#define power 4

#define left_neopixels 5
#define right_neopixels 6
#define nr_of_leds 34


double brightness = 1;

int r = 254;
int g = 0;
int b = 10;

int front_r = r;
int front_g = g;
int front_b = b;

int side_r = r;
int side_g = g;
int side_b = b;

int colors[][3] = {{255,0,0}, {0, 255, 0}, {0,0,255}, {0,255,100}, {10,255,255}};
int colors_len = 2;
int color_index = 0;

Adafruit_NeoPixel strip_left = Adafruit_NeoPixel(nr_of_leds, left_neopixels, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_right = Adafruit_NeoPixel(nr_of_leds, right_neopixels, NEO_GRB + NEO_KHZ800);

unsigned long powerOffTime = millis();
bool lastPowerState = 1;

CarCanbus* carCanbus;

void setup() {
  Serial.begin(9600);

  carCanbus = new CarCanbus();
  
  pinMode(sig, INPUT);
  pinMode(power, OUTPUT);


    
  digitalWrite(power, 1);

  strip_left.begin();  
  strip_right.begin();

  for(int i = 0; i < nr_of_leds; i++){
    strip_left.setPixelColor(i, 254, 0, 40);
    strip_right.setPixelColor(i, 254, 0, 40);
  }

     strip_left.show();
   strip_right.show();

}

void loop() {
    unsigned long addresses[254] = {};
    int index = 0;
    


    

  if(digitalRead(sig) != lastPowerState){ // If ignition changed
    lastPowerState = digitalRead(sig);
    powerOffTime = millis();
  }

  if(lastPowerState == 0 && (millis() - powerOffTime) > 8000){ // If the ignition state is off and 5 seconds expired
      digitalWrite(power, 0); // Turn off
  }
    
   set_front_led_color(front_r, front_g, front_b);         
   set_side_led_color(side_r, side_g, side_b);

   strip_left.show();
   strip_right.show();
}

void set_front_led_color(int r, int g, int b){
  r = r * brightness;
  g = g * brightness;
  b = b * brightness;

  for(int i = 0; i < 15; i++){
    strip_left.setPixelColor(i, r, g, b);
    strip_right.setPixelColor(i, r, g, b);
  }
}

void set_side_led_color(int r, int g, int b){
  r = r * brightness;
  g = g * brightness;
  b = b * brightness;
  
  for(int i = 15; i < nr_of_leds; i++){
    strip_left.setPixelColor(i, r, g, b);
    strip_right.setPixelColor(i, r, g, b);
  }
}

void set_whole_led_color(int r, int g, int b){
  for(int i = 0; i < nr_of_leds; i++){
    strip_left.setPixelColor(i, r, g, b);
    strip_right.setPixelColor(i, r, g, b);
  }
}




enum MainLedMode {OFF, COLOR, FADE, RAINBOW, TWINKLE, CHASE, FIRE, BALLS, TOTAL};

int current_main_led_mode = MainLedMode::COLOR;

void setNextMainMode(){
  if(current_main_led_mode == MainLedMode::TOTAL-1){
    current_main_led_mode = 0;
  }else{
    current_main_led_mode+=1;
  }
}

void setPreviousMainMode(){
  if(current_main_led_mode == 0){
    current_main_led_mode = MainLedMode::TOTAL-1;
  }else{
    current_main_led_mode-=1;
  }
}
