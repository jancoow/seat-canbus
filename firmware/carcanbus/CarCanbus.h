#ifndef CarCanbus_h
#define CarCanbus_h

#include <SPI.h>
#include "mcp_can.h"
#include "CarCanbusMessageHandler.h"
#include "messages/LightStatusCarCanbusMessageHandler.h"
#include "messages/WheelControlCarCanbusMessageHandler.h"
#include "messages/TurnSignalCarCanbusMessageHandler.h"
#include "messages/LeftDoorMessageHandler.h"
#include "messages/RightDoorMessageHandler.h"
#include "CarCanbusEventType.h"

#define CS_PIN 10

#define number_of_message_handlers 6

class CarCanbus{
  public:
    CarCanbus();
    CarCanbusEvent receiveMessage();

 private:
    MCP_CAN* mcpCan;
    unsigned char len = 0;
    unsigned char buf[8];
    
    CarCanbusMessageHandler* messageHandlers[number_of_message_handlers] = {
      new LightStatusCarCanbusMessageHandler(),
      new WheelControlCarCanbusMessageHandler(),
      new TurnSignalCarCanbusMessageHandler(),
      new LeftDoorCarCanbusMessageHandler(),
      new RightDoorCarCanbusMessageHandler()
    };

};
#endif
