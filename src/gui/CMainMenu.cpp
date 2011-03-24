#include "CMainMenu.h"

#include "listeners/CListenerMemberFn.h"
#include "CCenteredWindow.h"
#include "CCheckBox.h"
#include "CTextField.h"
#include "CText.h"
#include "CConsole.h"
#include "CBaseEngine.h"
#include "CListBox.h"
#include "CNewGame.h"
#include "CDownloadMaps.h"

CMainMenu::CMainMenu():
  CGuiPanel(vec2d(0,0),vec2d(engine->getScreenWidth(),engine->getScreenHeight()))
{
  fgColor.set(1., 1., 1., .7);
  bgColor.set(.25, .25, .25, .4);

  panelWidth=200;

  CGuiPanel* temp;

  addChild(new CLabel(vec2d(20,40),vec2d(15,15),"The"));
  addChild(new CLabel(vec2d(20,55),vec2d(30,30),"TSUEngine"));

  addChild(temp=new CButton(vec2d(20,100),vec2d(160,30),"Nová hra"));
  temp->addListener(makeCListenerMemberFn(1,this,&CMainMenu::buttonClicked));

  addChild(temp=new CButton(vec2d(20,135),vec2d(160,30),"Nastavení"));
  temp->addListener(makeCListenerMemberFn(2,this,&CMainMenu::buttonClicked));

  addChild(temp=new CButton(vec2d(20,170),vec2d(160,30),"Konzole"));
  temp->addListener(makeCListenerMemberFn(3,this,&CMainMenu::buttonClicked));

  temp=new CButton(vec2d(20,engine->getScreenHeight()-160),vec2d(160,30),"Ukončit");
  temp->addListener(makeCListenerMemberFn(0,this,&CMainMenu::buttonClicked));
  addChild(temp);

  addChild(_settings=new CCenteredWindow(vec2d(400,300), "Nastavení"));
  _settings->setVisible(false);
  _settings->addChild(new CTextField(vec2d(20, 50), vec2d(160,24)));

  CListBox* setList = new CListBox(vec2d(20, 100), vec2d(360, 180));
  setList->addItem("rofl");
  setList->addItem("test");
  setList->addItem("does it work?");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Definitely.");
  setList->addItem("rofl");
  setList->addItem("test");
  setList->addItem("does it work?");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Yes, yes it does!");
  setList->addItem("Definitely.");
  _settings->addChild(setList);

  addChild(_newGame=new CNewGame());
  _newGame->setVisible(false);

  addChild(_console=new CConsole());
  _console->setVisible(false);

  addChild(new CDownloadMaps());

  addChild(engine->m_tempConsoleOutput = new CText(vec2d(), vec2d(engine->getScreenWidth(), 80), 12));

  addChild(new CCheckBox(vec2d(20,210), vec2d(160,16), "Jinej test"));
  addChild(new CCheckBox(vec2d(20,230), vec2d(160,16), "Úplně jinej test"));
  addChild(new CCheckBox(vec2d(20,250), vec2d(160,16), "A ještě něco"));


}

void CMainMenu::draw(){
  drawVerticalGradient(0,0,panelWidth-1,getH(),bgColor,fgColor);
  setDrawColor(fgColor);
  drawQuad(panelWidth-1,0,1,getH());
}

void CMainMenu::buttonClicked(int id){
  switch(id){
    case 1: displayElement(_newGame); break;
    case 2: displayElement(_settings); break;
    case 3: displayElement(_console); break;
    case 0:
      engine->quit();
      break;
  }
}
