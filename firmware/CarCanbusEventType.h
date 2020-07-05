#ifndef CarCanbusEventType_h
#define CarCanbusEventType_h

enum CarCanbusEventType {
  noEvent,
  onLightIntensityChange,
  
  onLowBeamHeadLightsOn, onLowBeamHeadLightsOff,
  onFullBeamHeadLightsOn, onFullBeamHeadLightsOff,
  
  onVolumeUpPress,onVolumeDownPress,
  onModePress,
  onForwardPress, onBackwardsPress,
  onScrollUpPress, onScrollDownPress,

  onTurnLightLeftOn, onTurnLightLeftOff, 
  onTurnLightRightOn, onTurnLightRightOff,
  onHazardLightsOn, onHazardLightsOff,

  onLeftDoorOpen, onLeftDoorClose, onLeftDoorWindowUp, onLeftDoorWindowDown,
  onRightDoorOpen, onRightDoorClose, onRightDoorWindowUp, onRightDoorWindowDown
};

typedef struct {
  CarCanbusEventType eventType;
  uint16_t data;  
} CarCanbusEvent;

#endif
