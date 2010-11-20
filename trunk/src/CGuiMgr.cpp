#include "CGuiMgr.h"
#include "CGuiPanel.h"
#include "CMainMenu.h"
#include "const.h"
#include "macros.h"
#include "CBaseEngine.h"
#include "CCenteredWindow.h"

CGuiMgr::CGuiMgr(){}

void CGuiMgr::init(){
  _keyboardReceiver=NULL;
  _basePanel=new CGuiPanel(vec2d(0.,0.),vec2d(SCREENWIDTH,SCREENHEIGHT));

  _basePanel->addChild(new CMainMenu());


}

void CGuiMgr::update(){
  for(int i=0;i<NUMBUTTONS;i++){
    if(engine->input->buttonPressed((MouseButton)i)){
      _basePanel->handleMouseClick(engine->input->getCursor(),(MouseButton) i,false);
    }
    if(engine->input->buttonDepressed((MouseButton)i)){
      _basePanel->handleMouseClick(engine->input->getCursor(),(MouseButton) i,true);
    }
  }
  _basePanel->handleMouseMove(engine->input->getCursor(),true);
  if(_keyboardReceiver && _keyboardReceiver->isVisible()){
    std::wstring input = engine->input->getString();
    if(!input.empty()){
      _keyboardReceiver->onKeyboard(input);
    }else{
    }
  }
}

void CGuiMgr::drawElements(){
  glDisable(GL_TEXTURE_2D);
  _basePanel->draw();
  _basePanel->drawChildren();
}