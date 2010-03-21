#include <string>
#include <gl/gl.h>
#include <ctime>
#include "globals.h"
#include "const.h"
#include "datatypes.h"
#include "CBaseEntity.h"
#include "CEntMgr.h"
#include "CInputMgr.h"
#include "CGuiMgr.h"
#include "GLFT_Font.hpp"

#ifndef CBASEENGINE_H
#define CBASEENGINE_H

class CBaseEngine{
  private:
    rgba            drawColor;
    vec3d           drawPos;


    //time vars
    clock_t         lastClock;
    double          time;
    double          lastTime;
    double          timeDelta;
    double          realTime;
    double          lastRealTime;
    double          realTimeDelta;
    double          timeScale;
    unsigned long long int    frameCount;
    double          fps;

    GLFT_Font       fnt;


  public:
    CEntMgr*        ents;
    CInputMgr*      input;
    CGuiMgr*        gui;


                    CBaseEngine(){};
                    //~CBaseEngine(){};
    void            init();
    void            destroy();
    void            setDrawPos(double x, double y, double z);
    void            setDrawPos(vec3d pos);
    void            setDrawColor(float r, float g, float b, float a);
    void            setDrawColor(rgba col);
    void            drawModel(int wmId);
    double          getTime();
    double          getLastTime();
    double          getTimeDelta();
    double          getRealTime();
    double          getLastRealTime();
    double          getRealTimeDelta();
    unsigned long long int getFrameCount();
    double          getFPS();
    void            createEntity(std::string name);

    void            think();
    void            initWorldView();
    void            initGuiView();
    void            drawScene();


};

#endif
