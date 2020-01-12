#include "CarCanbus.h"

CarCanbus::CarCanbus(){
  this->mcpCan = new MCP_CAN(CS_PIN);
  while (CAN_OK != mcpCan->begin(CAN_200KBPS))
  {
      Serial.println("CAN BUS Init Failed");
      delay(100);
  }
  Serial.println("CAN BUS  Init OK!");
}

void CarCanbus::receiveMessage(){
  if(CAN_MSGAVAIL == mcpCan->checkReceive()){
        mcpCan->readMsgBuf(&len, buf);
        unsigned long canId = mcpCan->getCanId();

        switch(canId){
          case wheel_control:
            break;
          case light_status:
            break;
          default:
            break;
        }

//        if(canId == wheel_control){
//           if(buf[0] == scroll_up){
//              color_index++;
//           }else if(buf[0] == scroll_down){
//              color_index--;
//           }
//           
//           if(color_index > colors_len)
//              color_index = 0;
//           if(color_index < 0)
//            color_index = colors_len;
//
//         r = colors[color_index][0];
//           g = colors[color_index][1];
//           b = colors[color_index][2];
//
//           front_r = r;
//           front_g = g;
//           front_b = b;
//           side_r = r;
//           side_g = g;
//           side_b = b;
//            
//           
//
//
//           Serial.println(index);
//
//        }
//
//        if(canId == light_status){
//          if(buf[flash_light_index] == flash_light_on){
//            front_r = front_g = front_b = 254;
//          }else{
//            front_r = r;
//            front_g = g;
//            front_b = b;
//          }
//          if(buf[light_status_index] != light_status_off){
//            brightness = map(buf[dashboard_light_intensity_index], 19, 35, 50, 255) / 255.0;
//          }else{
//            brightness = 1;
//          }
//        }
    }
}
