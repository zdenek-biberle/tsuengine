#ifndef CINPUTMGR_H
#define CINPUTMGR_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "datatypes.h"

class CInputMgr{
  public:
                   CInputMgr();
                   ~CInputMgr();
    void           init();
    void           update();
    bool           keyDown(int key);
    bool           keyStillDown(int key);
    bool           keyPressed(int key);
    bool           keyDepressed(int key);
    float          keyTimed(int key);
    float          keyTimedDelta(int key);
    float          keyRealTimed(int key);
    float          keyRealTimedDelta(int key);

    bool           buttonDown(MouseButton button);
    bool           buttonPressed(MouseButton button);
    bool           buttonDepressed(MouseButton button);


    const float    getX() const;
    const float    getY() const;
    const vec2d    getCursor() const;
    const float    getXDelta() const;
    const float    getYDelta() const;

    DIMOUSESTATE2  MouseState[2];
    char           keyBuffer[2][256];
    double         keyTimeBuffer[2][256];
    double         keyRealTimeBuffer[2][256];
  private:
    LPDIRECTINPUT8 DIObject;
    LPDIRECTINPUTDEVICE8 DIKeyboardDevice;

    LPDIRECTINPUTDEVICE8 DIMouseDevice;

    bool                 bInverted;           //inverted y axis (NEW)
    int                  iCurrBuffer;
    float                fSensitivity;        //mouse sensitivity (NEW)
    vec2d                cursor;
    int                  iAxes,              //number of axes (NEW)
                         iButtons;           //number of buttons (NEW)
};

inline const float CInputMgr::getX() const{
  return cursor.x;
}

inline const float CInputMgr::getY() const{
  return cursor.y;
}

inline const vec2d CInputMgr::getCursor() const{
  return cursor;
}

inline const float CInputMgr::getXDelta() const{
  return MouseState[iCurrBuffer].lX;
}

inline const float CInputMgr::getYDelta() const{
  return MouseState[iCurrBuffer].lY;
}


#endif