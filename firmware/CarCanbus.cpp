#include "CarCanbus.h"

CarCanbus::CarCanbus(){
  this->mcpCan = new MCP_CAN(CS_PIN);
  while (CAN_OK != mcpCan->begin(CAN_200KBPS))
  {
      Serial.println("CAN BUS Init Failed");
      delay(100);
  }
  Serial.println("CAN BUS Init OK!");
}

CarCanbusEvent CarCanbus::receiveMessage(){
  if(CAN_MSGAVAIL == mcpCan->checkReceive()){
        mcpCan->readMsgBuf(&len, buf);
        unsigned long canId = mcpCan->getCanId();
        
        Serial.print(canId, HEX);
        Serial.print(":");
        for(int i = 0; i < 8; i++){
           Serial.print(buf[i]);
           Serial.print("  ");
        }
        Serial.println();
        
        for(int i = 0; i < number_of_message_handlers; i++){
          if(this->messageHandlers[i]->address == canId){
              return this->messageHandlers[i]->handleMessage(buf);
          }
        }
    }
    return {noEvent, 0};
}
