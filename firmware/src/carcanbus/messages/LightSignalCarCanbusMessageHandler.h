#ifndef LightSignalCarCanbusMessageType_h
#define LightSignalCarCanbusMessageType_h

#include "../CarCanbusMessageHandler.h"

#define light_signal_address 0x531
#define light_signal_idx 1

#define turn_signal_mask 0b00011111
#define brake_signal_mask 0b11000000

#define turn_signal_status_off 0
#define turn_signal_status_left 17
#define turn_signal_status_right 18
#define turn_signal_status_hazard 27           
#define brake_lights             64

class LightSignalCarCanbusMessageHandler: public CarCanbusMessageHandler {
  public:
    uint8_t turnSignalStatus;
    uint8_t brakeSignalStatus;

    LightSignalCarCanbusMessageHandler() : CarCanbusMessageHandler(light_signal_address) {};

    CarCanbusEvent handleMessage(unsigned char *message) {
      uint8_t turnSignalStatus = message[light_signal_idx] & turn_signal_mask;
      uint8_t brakeSignalStatus = message[light_signal_idx] & brake_signal_mask;
      CarCanbusEvent event = {noEvent, 0};
      
      if (this->turnSignalStatus != turnSignalStatus) {
        if(turnSignalStatus == turn_signal_status_off){
          if(this->turnSignalStatus == turn_signal_status_left){
            event = {onTurnLightLeftOff, 0};         
          }else if(this->turnSignalStatus == turn_signal_status_right){
            event = {onTurnLightRightOff, 0};  
          }else if(this->turnSignalStatus == turn_signal_status_hazard){
            event = {onHazardLightsOff, 0};             
          }
        }else if(turnSignalStatus == turn_signal_status_left){
          event = {onTurnLightLeftOn, 0};         
        }else if(turnSignalStatus == turn_signal_status_right){
          event = {onTurnLightRightOn, 0};  
        }else if(turnSignalStatus == turn_signal_status_hazard){
          event = {onHazardLightsOn, 0};             
        }

        this->turnSignalStatus = turnSignalStatus;

        return event;
      }


      if(this->brakeSignalStatus != brakeSignalStatus){
        if(brakeSignalStatus == brake_lights){
          event = {onBrakeLightsOn, 0};
        }else{
          event = {onBrakeLightsOff, 0};
        }
        
        this->brakeSignalStatus = brakeSignalStatus;
      }

      return event;
    }
};

#endif
