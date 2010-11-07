#include "CLabel.h"
#include <string>
#include "vec2d.h"
#include "CGuiPanel.h"
#include "macros.h"
#include "CBaseEngine.h"
#include <gl/gl.h>



CLabel::CLabel(const vec2d& position, const vec2d& size, const std::wstring& text, ALIGN align):
CGuiPanel(position,size),
_text(text)
{
  allowKeyboardInput=false;
  _font=engine->fonts->getFont(L"ARIALUNI.TTF",getH());
}

void CLabel::draw(){
  setDrawColor(fgColor);
  _font->render(getH(),_text,fgColor);
}

void CLabel::updateFont(){
}
