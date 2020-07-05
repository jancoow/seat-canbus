#ifndef WheelControlCarCanbusMessageType_h
#define WheelControlCarCanbusMessageType_h

#include "CarCanbusMessageHandler.h"

#define wheel_control_address 0x5c1

#define vol_up            6
#define vol_down          7
#define mode              1
#define forwards          4
#define backwards         5
#define scroll_up         2
#define scroll_down       3

class WheelControlCarCanbusMessageHandler: public CarCanbusMessageHandler{
  public:
    uint8_t lastPressedButton;
    WheelControlCarCanbusMessageHandler() : CarCanbusMessageHandler(wheel_control_address){};
    
    CarCanbusEvent handleMessage(unsigned char *message){
      uint8_t button = message[0];
      if(button != lastPressedButton){      
         lastPressedButton = button;

         if(button == vol_up) return {onVolumeUpPress, 0};
         if(button == vol_down) return {onVolumeDownPress, 0};
         if(button == mode) return {onModePress, 0};
         if(button == forwards) return {onForwardPress, 0};
         if(button == backwards) return {onBackwardsPress, 0};
         if(button == scroll_up) return {onScrollUpPress, 0};
         if(button == scroll_down) return {onScrollDownPress, 0};
      }

      return {noEvent, 0};
    }
};

#endif
