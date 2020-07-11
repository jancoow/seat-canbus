#ifndef CarCanbusMessageType_h
#define CarCanbusMessageType_h

#include "CarCanbusEventType.h"

class CarCanbusMessageHandler{
  public:
    uint16_t const address; 

    virtual CarCanbusEvent handleMessage(unsigned char *message){return {noEvent, 0};};
  protected:
     CarCanbusMessageHandler(uint16_t address) : address(address){};
};

#endif
