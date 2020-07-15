#include "carcanbus/CarCanbus.h"
#include "carcanbus/CarCanbusEventType.h"
#include "carled/CarLed.h"

#define sig 2
#define power 4


int r = 254;
int g = 0;
int b = 10;

int front_r = r;
int front_g = g;
int front_b = b;

int side_r = r;
int side_g = g;
int side_b = b;

unsigned long powerOffTime = millis();
bool lastPowerState = 1;

CarLed* carLed;
CarCanbus* carCanbus;
CarCanbusEvent event;

void setup() {
  Serial.begin(115200);

  pinMode(sig, INPUT);
  pinMode(power, OUTPUT);

  digitalWrite(power, 1);

  carCanbus = new CarCanbus();
  carLed = new CarLed();
}


void loop() {

   event = carCanbus->receiveMessage();

   if(event.eventType != noEvent){
      Serial.print("Event happened!: ");
      Serial.println(event.eventType);
      carLed->handleEvent(&event);
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

// void set_front_led_color(int r, int g, int b){
//   r = r * brightness;
//   g = g * brightness;
//   b = b * brightness;

//   for(int i = 0; i < 15; i++){
//     strip_left.setPixelColor(i, r, g, b);
//     strip_right.setPixelColor(i, r, g, b);
//   }

//   strip_left.show();
//   strip_right.show();
// }

// void set_left_front_led_color(int r, int g, int b){
//   r = r * brightness;
//   g = g * brightness;
//   b = b * brightness;

//   for(int i = 0; i < 15; i++){
//     strip_left.setPixelColor(i, r, g, b);
//   }

//   strip_left.show();
// }

// void set_right_front_led_color(int r, int g, int b){
//   r = r * brightness;
//   g = g * brightness;
//   b = b * brightness;

//   for(int i = 0; i < 15; i++){
//     strip_right.setPixelColor(i, r, g, b);
//   }
  
//   strip_right.show();
// }

// void set_side_led_color(int r, int g, int b){
//   r = r * brightness;
//   g = g * brightness;
//   b = b * brightness;
  
//   for(int i = 15; i < nr_of_leds; i++){
//     strip_left.setPixelColor(i, r, g, b);
//     strip_right.setPixelColor(i, r, g, b);
//   }

//   strip_left.show();
//   strip_right.show();
// }

// void set_left_side_led_color(int r, int g, int b){
//   r = r * brightness;
//   g = g * brightness;
//   b = b * brightness;
  
//   for(int i = 15; i < nr_of_leds; i++){
//     strip_left.setPixelColor(i, r, g, b);
//   }

//   strip_left.show();
// }

// void set_right_side_led_color(int r, int g, int b){
//   r = r * brightness;
//   g = g * brightness;
//   b = b * brightness;
  
//   for(int i = 15; i < nr_of_leds; i++){
//     strip_right.setPixelColor(i, r, g, b);
//   }

//   strip_right.show();
// }

// void set_whole_led_color(int r, int g, int b){
//   for(int i = 0; i < nr_of_leds; i++){
//     strip_left.setPixelColor(i, r, g, b);
//     strip_right.setPixelColor(i, r, g, b);
//   }
//    strip_left.show();
//   strip_right.show();
// }

// void set_preset_color(){
//      if(color_index > colors_len)
//            color_index = 0;
//      if(color_index < 0)
//            color_index = colors_len;

//      set_whole_led_color(colors[color_index][0], colors[color_index][1], colors[color_index][2]);
// }


