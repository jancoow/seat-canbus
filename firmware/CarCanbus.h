#include <SPI.h>
#include "mcp_can.h"

#ifndef CarCanbus_h
#define CarCanbus_h

#define CS_PIN 10

// Address defines
#define wheel_control   0x5c1
#define light_status    0x621

// messages
// WHEEL buf 0
#define vol_up            6
#define vol_down          7
#define mode              1
#define forwards          4
#define backwards         5
#define scroll_up         2
#define scroll_down       3

// light status buf index
#define dashboard_light_intensity_index 6

#define light_status_index 5
#define light_status_off 0

#define flash_light_index 4
#define flash_light_off 1
#define flash_light_on 0x21


class CarCanbus{
  public:
    CarCanbus();
    void receiveMessage();

 private:
    MCP_CAN* mcpCan;
    unsigned char len = 0;
    unsigned char buf[8];
 
};
#endif
