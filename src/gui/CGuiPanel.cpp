#include "CGuiPanel.h"
#include "macros.h"
#include <gl/gl.h>
#include "CActionListener.h"

CGuiPanel::~CGuiPanel(){
  int size=children.size();
  for (int i=0; i<size; i++){
    removeChild(i);
  }
}

CGuiPanel::CGuiPanel(const vec2d& position, const vec2d& size){
  init();
  this->position=position;
  this->size=size;
}

void CGuiPanel::init(){
  position.set(0.,0.);
  parent=NULL;
  opacity=1.;
  visible=true;
  mouseOver=false;
  mouseDown=false;
  children.reserve(8);
  allowMouseClickPropagation=true;
  //MSGBOX("New CGuiPanel inited/created");
  fgColor.set(1.,1.,1.,1.);
  bgColor.set(0.,0.,0.,.25);
  glossColor.set(1., 1., 1., .1);
}



void CGuiPanel::addChild(CGuiPanel* newChild){
  newChild->setParent(this);
  newChild->setParentIndex(children.size());
  children.push_back(newChild);
}

void CGuiPanel::removeChild(CGuiPanel* child){
  int size=children.size();
  for (int i=0; i<size; i++){
    if(children.at(i)==child){
      removeChild(i);
      break;
    }
  }
}

void CGuiPanel::removeChild(int childIndex){
  children.at(childIndex)->setParent(NULL);
  children.erase(children.begin()+childIndex);
}

void CGuiPanel::draw(){
}

void CGuiPanel::drawChildren(){
  int size=children.size();
  for (ChildrenList::iterator i = children.begin(); i != children.end(); ++i){
    CGuiPanel* child=*i;
    if(child->getVisible()){
      glPushMatrix();
      glTranslatef(child->getX(),child->getY(),0.);
      child->draw();
      child->drawChildren();
      glPopMatrix();
    }
  }
}

void CGuiPanel::requestFocus(){
  parent->giveFocusTo(parentIndex);
}

void CGuiPanel::giveFocusTo(int childIndex){
  if(children.size()-1!=childIndex){         //if the child already has focus, do nothing
    CGuiPanel* temp = children.at(childIndex);
    children.erase(children.begin()+childIndex);
    children.push_back(temp);

    //now update the indexes for affected children
    for(int i=childIndex;i<children.size();i++){
      children.at(i)->setParentIndex(i);
    }
  }
}

std::string CGuiPanel::toString(){
  char buff[1024];
  //sprintf(buff,"CGuiPanel[x=%.0lf,y=%.0lf,w=%.0lf,h=%.0lf]",position.x,position.y,size.x,size.y);
  std::string ret=buff;
  return ret;
}

bool CGuiPanel::handleMouseClick(const vec2d& position, const MouseButton button, const bool up){
  for(int i=children.size()-1;i>=0;i--){
    vec2d positionInChild = position-(children.at(i)->getPosition());
    CGuiPanel* child=children.at(i);
    if( child->getVisible() && children.at(i)->isPointInside( positionInChild ) ){
      if(children.at(i)->handleMouseClick(positionInChild, button, up)){
        break;
      }else{
        return false;
      }
    }
  }
  bool wasMouseDown=mouseDown;
  mouseDown=!up;
  if(wasMouseDown && up){
    onMouseClick(position,button);
  }
  up?onMouseUp(position,button):onMouseDown(position,button);
  return allowMouseClickPropagation;
}

void CGuiPanel::onMouseDown(const vec2d& position, const MouseButton button){
}

void CGuiPanel::onMouseUp(const vec2d& position, const MouseButton button){
}

void CGuiPanel::onMouseClick(const vec2d& position, const MouseButton button){
}

void CGuiPanel::handleMouseMove(const vec2d& newPosition, const bool mouseOver){
  vec2d positionInChild;
  bool itemFound=false;

  for(int i=children.size()-1;i>=0;i--){
    CGuiPanel* child=children.at(i);
    positionInChild = newPosition-(child->getPosition());
    if(!itemFound && child->getVisible() && child->isPointInside( positionInChild )){
      child->handleMouseMove( positionInChild, true);
      itemFound=true;
    }else{
      if(child->getMouseOver()){
        child->handleMouseMove( positionInChild, false);
      }
    }
  }
  if(getMouseOver() && !mouseOver){
    onMouseOut();
  }
  if(!getMouseOver() && mouseOver){
    onMouseOver();
  }

  this->mouseOver=mouseOver;

  if(newPosition.x!=0. && newPosition.y!=0.){
    mouseMove(newPosition,mouseOver);
  }
}

void CGuiPanel::mouseMove(const vec2d& positionDelta,const bool mouseOver){
}

void CGuiPanel::onMouseOver(){
}

void CGuiPanel::onMouseOut(){
}

void CGuiPanel::addActionListener(CActionListener* al){
  actionListeners.push_back(al);
  al->setOriginator(this);
}

void CGuiPanel::drawQuad(float x, float y, float w, float h){
  glBegin(GL_QUADS);
  glVertex2f(x,y);
  glVertex2f(x+w,y);
  glVertex2f(x+w,y+h);
  glVertex2f(x,y+h);
  glEnd();
}

void CGuiPanel::drawVerticalGradient(float x, float y, float w, float h, const rgba& colOne, const rgba& colTwo){
  glBegin(GL_QUADS);
  setDrawColor(colOne);
  glVertex2f(x,y);
  glVertex2f(x+w,y);
  setDrawColor(colTwo);
  glVertex2f(x+w,y+h);
  glVertex2f(x,y+h);
  glEnd();
}

void CGuiPanel::drawHorizontalGradient(float x, float y, float w, float h, const rgba& colOne, const rgba& colTwo){
  glBegin(GL_QUADS);
  setDrawColor(colOne);
  glVertex2f(x,y+h);
  glVertex2f(x,y);
  setDrawColor(colTwo);
  glVertex2f(x+w,y);
  glVertex2f(x+w,y+h);
  glEnd();
}

void CGuiPanel::drawFrame(float x, float y, float w, float h){
  drawQuad(x,      y+1,    1.,   h-2.);
  drawQuad(x+1.,   y,      w-2., 1.);
  drawQuad(x+w-1., y+1.,   1.,   h-2);
  drawQuad(x+1.,   y+h-1., w-2., 1.);
}

void CGuiPanel::setDrawColor(const rgba& color){
  glColor4f(color.r,color.g,color.b,color.a);
}

void CGuiPanel::fireListeners(){
  for(ActionListenerList::iterator it = actionListeners.begin(); it!=actionListeners.end(); ++it){
    (*it)->actionPerformed();
  }
}