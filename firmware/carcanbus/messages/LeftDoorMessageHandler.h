#ifndef LeftDoorCarCanbusMessageHandler_h
#define LeftDoorCarCanbusMessageHandler_h

#include "../CarCanbusMessageHandler.h"

#define left_door_address 0x381

#define left_door_status  0
#define left_window_status  2

class LeftDoorCarCanbusMessageHandler: public CarCanbusMessageHandler{
  public:
    uint8_t doorStatus;
    uint8_t windowHeight;

    LeftDoorCarCanbusMessageHandler() : CarCanbusMessageHandler(left_door_address){};
    
    CarCanbusEvent handleMessage(unsigned char *message){
      CarCanbusEvent event = {noEvent, 0};
      
      if(message[left_door_status] != doorStatus){
        doorStatus = message[left_door_status];
        if(message[left_door_status] == 1){
          return {onLeftDoorOpen, 0};
        }else if(message[left_door_status] == 0){
          return {onLeftDoorClose, 0};
        }      
      }else if(message[windowHeight] != windowHeight){
        if(message[windowHeight] > windowHeight){
           event = {onLeftDoorWindowUp, message[windowHeight]};
        }else{
          event = {onLeftDoorWindowDown, message[windowHeight]};
        }
        windowHeight = message[windowHeight];
      }

      return event;
    }
};

#endif
