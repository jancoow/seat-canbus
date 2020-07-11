#ifndef LightStatusCarCanbusMessageType_h
#define LightStatusCarCanbusMessageType_h

#include "../CarCanbusMessageHandler.h"

#define light_status_address 0x621

#define light_intensity_index 6

#define low_beam_light_index 5
#define low_beam_light_off 0
#define low_beam_light_on 1

#define full_beam_light_index 4
#define full_beam_light_off 1
#define full_beam_light_on 0x21

class LightStatusCarCanbusMessageHandler: public CarCanbusMessageHandler{
  public:
    uint8_t lowBeamLightStatus;    
    uint8_t fullBeamLightStatus;    
    uint16_t lightIntensity;

    LightStatusCarCanbusMessageHandler(): CarCanbusMessageHandler(light_status_address){};
    
    CarCanbusEvent handleMessage(unsigned char *message){
      // Low beam light status changed
      if(lowBeamLightStatus != message[low_beam_light_index]){
        lowBeamLightStatus = message[low_beam_light_index];

        if(lowBeamLightStatus == low_beam_light_off){
          return {onLowBeamHeadLightsOff, 0};
        }else if(lowBeamLightStatus == low_beam_light_on){
          return {onLowBeamHeadLightsOn, 0};
        }
      }

      // Full beam light status changed
      if(fullBeamLightStatus != message[full_beam_light_index]){
        fullBeamLightStatus = message[full_beam_light_index];

        if(fullBeamLightStatus == full_beam_light_off){
          return {onFullBeamHeadLightsOff, 0};
        }else if(fullBeamLightStatus == full_beam_light_on){
          return {onFullBeamHeadLightsOn, 0};
        }
      }

      // Light intensity changed
      if(lightIntensity != ((message[light_intensity_index]<<8) | message[light_intensity_index+1])){
        lightIntensity =  ((message[light_intensity_index]<<8) | message[light_intensity_index+1]);
        return {onLightIntensityChange, lightIntensity};
      }

      return {noEvent, 0};
    }
};

#endif
