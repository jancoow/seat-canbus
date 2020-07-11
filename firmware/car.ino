#include <Adafruit_NeoPixel.h> 
#include "carcanbus/CarCanbus.h"
#include "carcanbus/CarCanbusEventType.h"

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

int colors[][10] = {{255,0,0}, {0, 255, 0}, {0,0,255}, {0,255,100}, {10,255,255}, {57, 106, 177}, {218, 124, 48}, {62, 150, 81}, {204, 37, 41}, {107, 76, 154}};
int colors_len = 10;
int color_index = 0;

Adafruit_NeoPixel strip_left = Adafruit_NeoPixel(nr_of_leds, left_neopixels, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_right = Adafruit_NeoPixel(nr_of_leds, right_neopixels, NEO_GRB + NEO_KHZ800);

unsigned long powerOffTime = millis();
bool lastPowerState = 1;

CarCanbus* carCanbus;
CarCanbusEvent event;

void setup() {
  Serial.begin(115200);

  carCanbus = new CarCanbus();
  
  pinMode(sig, INPUT);
  pinMode(power, OUTPUT);

  digitalWrite(power, 1);

  strip_left.begin();  
  strip_right.begin();

  for(int i = 0; i < nr_of_leds; i++){
    strip_left.setPixelColor(i, 200, 50, 0);
    strip_right.setPixelColor(i, 200, 50, 0);
  }

  strip_left.show();
  strip_right.show();
}


void loop() {

   event = carCanbus->receiveMessage();

   if(event.eventType != noEvent){
      Serial.print("Event happened!: ");
      Serial.println(event.eventType);
      if(event.eventType == onTurnLightLeftOn){
        set_left_side_led_color(255, 165, 0);
      }else if(event.eventType == onTurnLightLeftOff){
        set_left_side_led_color(0, 0, 0);
      }else if(event.eventType == onTurnLightRightOn){
        set_right_side_led_color(255, 165, 0);
      }else if(event.eventType == onTurnLightRightOff){
        set_right_side_led_color(0, 0, 0);
      }else if(event.eventType == onHazardLightsOn){
        set_side_led_color(255, 165, 0);
      }else if(event.eventType == onHazardLightsOff){
        set_side_led_color(0, 0, 0);
      }else if(event.eventType == onLeftDoorOpen){
        set_left_front_led_color(255, 0, 0);
      }else if(event.eventType == onLeftDoorClose){
        set_left_front_led_color(0, 0, 0);
      }else if(event.eventType == onRightDoorOpen){
        set_right_front_led_color(255, 0, 0);
      }else if(event.eventType == onLeftDoorClose){
        set_right_front_led_color(0, 0, 0);
      }else if(event.eventType == onScrollUpPress){
         color_index++;
         set_preset_color();
      }else if(event.eventType == onScrollDownPress){
        color_index--;
        set_preset_color();
      }
    }

  //if(digitalRead(sig) != lastPowerState){ // If ignition changed
  //  lastPowerState = digitalRead(sig);
  //  powerOffTime = millis();
  //}

  //if(lastPowerState == 0 && (millis() - powerOffTime) > 8000){ // If the ignition state is off and 5 seconds expired
  //    digitalWrite(power, 0); // Turn off
  //}
    
   //set_front_led_color(front_r, front_g, front_b);         
   //set_side_led_color(side_r, side_g, side_b);

   //strip_left.show();
   //strip_right.show();
}

void set_front_led_color(int r, int g, int b){
  r = r * brightness;
  g = g * brightness;
  b = b * brightness;

  for(int i = 0; i < 15; i++){
    strip_left.setPixelColor(i, r, g, b);
    strip_right.setPixelColor(i, r, g, b);
  }

  strip_left.show();
  strip_right.show();
}

void set_left_front_led_color(int r, int g, int b){
  r = r * brightness;
  g = g * brightness;
  b = b * brightness;

  for(int i = 0; i < 15; i++){
    strip_left.setPixelColor(i, r, g, b);
  }

  strip_left.show();
}

void set_right_front_led_color(int r, int g, int b){
  r = r * brightness;
  g = g * brightness;
  b = b * brightness;

  for(int i = 0; i < 15; i++){
    strip_right.setPixelColor(i, r, g, b);
  }
  
  strip_right.show();
}

void set_side_led_color(int r, int g, int b){
  r = r * brightness;
  g = g * brightness;
  b = b * brightness;
  
  for(int i = 15; i < nr_of_leds; i++){
    strip_left.setPixelColor(i, r, g, b);
    strip_right.setPixelColor(i, r, g, b);
  }

  strip_left.show();
  strip_right.show();
}

void set_left_side_led_color(int r, int g, int b){
  r = r * brightness;
  g = g * brightness;
  b = b * brightness;
  
  for(int i = 15; i < nr_of_leds; i++){
    strip_left.setPixelColor(i, r, g, b);
  }

  strip_left.show();
}

void set_right_side_led_color(int r, int g, int b){
  r = r * brightness;
  g = g * brightness;
  b = b * brightness;
  
  for(int i = 15; i < nr_of_leds; i++){
    strip_right.setPixelColor(i, r, g, b);
  }

  strip_right.show();
}

void set_whole_led_color(int r, int g, int b){
  for(int i = 0; i < nr_of_leds; i++){
    strip_left.setPixelColor(i, r, g, b);
    strip_right.setPixelColor(i, r, g, b);
  }
   strip_left.show();
  strip_right.show();
}

void set_preset_color(){
     if(color_index > colors_len)
           color_index = 0;
     if(color_index < 0)
           color_index = colors_len;

     set_whole_led_color(colors[color_index][0], colors[color_index][1], colors[color_index][2]);
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
