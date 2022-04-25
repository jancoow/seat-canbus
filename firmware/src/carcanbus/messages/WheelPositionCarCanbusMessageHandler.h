#ifndef WheelPositionCarCanbusMessageType_h
#define WheelPositionCarCanbusMessageType_h

#include "../CarCanbusMessageHandler.h"

#define wheel_position_address 0x3c3



class WheelPositionCarCanbusMessageHandler: public CarCanbusMessageHandler{
  public:
    uint8_t lastWheelPosition;
    WheelPositionCarCanbusMessageHandler() : CarCanbusMessageHandler(wheel_position_address){};
    
    CarCanbusEvent handleMessage(unsigned char *message){
      uint8_t wheelPosition = message[0];
      if(wheelPosition != lastWheelPosition){      
         lastWheelPosition = wheelPosition;

         return {onWheelPositionChanged, wheelPosition};
      }

      return {noEvent, 0};
    }
};

#endif
