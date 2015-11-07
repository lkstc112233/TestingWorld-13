#include "stdafx.h"
#include "Entity.h"

CEntity::CEntity()
{
}


CEntity::~CEntity()
{
}

void CEntity::setModule(shared_ptr<CDotModule> module)
{
	m_module = module;
}
