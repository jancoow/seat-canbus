#ifndef TurnSignalCarCanbusMessageType_h
#define TurnSignalCarCanbusMessageType_h

#include "../CarCanbusMessageHandler.h"

#define turn_signal_address 0x531

#define turn_signal_status 1

#define turn_signal_status_off 0
#define turn_signal_status_left 17
#define turn_signal_status_right 18
#define turn_signal_status_hazard 27           

class TurnSignalCarCanbusMessageHandler: public CarCanbusMessageHandler {
  public:
    uint8_t turnSignalStatus;

    TurnSignalCarCanbusMessageHandler() : CarCanbusMessageHandler(turn_signal_address) {};

    CarCanbusEvent handleMessage(unsigned char *message) {
      uint8_t turnSignalStatus = message[turn_signal_status];
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
      }

      return event;
    }
};

#endif
