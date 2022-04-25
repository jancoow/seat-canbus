#include "carcanbus/CarCanbus.h"
#include "carcanbus/CarCanbusEventType.h"
#include "carled/CarLedController.h"

CarLedController* carLedController;
CarCanbus* carCanbus;
CarCanbusEvent event;

void setup() {
  Serial.begin(115200);

  carCanbus = new CarCanbus();
  carLedController = new CarLedController();
}


void loop() {
   event = carCanbus->receiveMessage();

   if(event.eventType != noEvent){
      Serial.print("Event happened!: ");
      Serial.print(event.eventType);
      Serial.println(event.data);
      carLedController->handleEvent(&event);
    }
  carLedController->tick();
  delay(0.001);
}

