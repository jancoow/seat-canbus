#ifndef RightDoorCarCanbusMessageHandler_h
#define RightDoorCarCanbusMessageHandler_h

#include "../CarCanbusMessageHandler.h"

#define right_door_address 0x3B5

#define right_door_status  0
#define right_window_status  2

class RightDoorCarCanbusMessageHandler: public CarCanbusMessageHandler{
  public:
    uint8_t doorStatus;
    uint8_t windowHeight;

    RightDoorCarCanbusMessageHandler() : CarCanbusMessageHandler(right_door_address){};
    
    CarCanbusEvent handleMessage(unsigned char *message){
      CarCanbusEvent event = {noEvent, 0};
      
      if(message[right_door_status] != doorStatus){
        doorStatus = message[right_door_status];
        if(message[right_door_status] == 1){
          return {onRightDoorOpen, 0};
        }else if(message[right_door_status] == 0){
          return {onRightDoorClose, 0};
        }      
      }else if(message[right_window_status] != windowHeight){
        if(message[right_window_status] > windowHeight){
           event = {onRightDoorWindowUp, message[right_window_status]};
        }else{
          event = {onRightDoorWindowDown, message[right_window_status]};
        }
        windowHeight = message[right_window_status];
      }

      return event;
    }
};

#endif
