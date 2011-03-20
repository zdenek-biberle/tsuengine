#include "CPropDynamic.h"
#include "DescriptorList.h"

#include "CBaseEngine.h"

void CPropDynamic::spawn(){
  m_model->linkToEntity(this);
  m_model->setPhysics(P_DYNAMIC);
}

REGISTER_ENTITY(CPropDynamic)
