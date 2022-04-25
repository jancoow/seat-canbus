#ifndef CarCanbus_h
#define CarCanbus_h

#include <SPI.h>
#include "mcp_can.h"
#include "CarCanbusMessageHandler.h"
#include "messages/LightStatusCarCanbusMessageHandler.h"
#include "messages/WheelControlCarCanbusMessageHandler.h"
#include "messages/LightSignalCarCanbusMessageHandler.h"
#include "messages/LeftDoorMessageHandler.h"
#include "messages/RightDoorMessageHandler.h"
#include "messages/WheelPositionCarCanbusMessageHandler.h"
#include "CarCanbusEventType.h"

#define CS_PIN 10
#define INT_PIN 2
#define number_of_message_handlers 6

class CarCanbus{
  public:
    CarCanbus(){
      pinMode(INT_PIN, INPUT);
      this->mcpCan = new MCP_CAN(CS_PIN);
      while (CAN_OK != mcpCan->begin(CAN_200KBPS))
      {
          Serial.println("CAN BUS Init Failed");
          delay(100);
      }
      Serial.println("CAN BUS Init OK!");
    }

    CarCanbusEvent receiveMessage(){
      if(CAN_MSGAVAIL == mcpCan->checkReceive()){
            mcpCan->readMsgBuf(&len, buf);
            unsigned long canId = mcpCan->getCanId();
            
            for(int i = 0; i < number_of_message_handlers; i++){
              if(this->messageHandlers[i]->address == canId){
                  return this->messageHandlers[i]->handleMessage(buf);
              }
            }
        }
        return {noEvent, 0};
    }

 private:
    MCP_CAN* mcpCan;
    unsigned char len = 0;
    unsigned char buf[8];
    
    CarCanbusMessageHandler* messageHandlers[number_of_message_handlers] = {
      new LightStatusCarCanbusMessageHandler(),
      new WheelControlCarCanbusMessageHandler(),
      new LightSignalCarCanbusMessageHandler(),
      new LeftDoorCarCanbusMessageHandler(),
      new RightDoorCarCanbusMessageHandler()
      // new WheelPositionCarCanbusMessageHandler()
    };

};
#endif
