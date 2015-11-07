#include "stdafx.h"
#include "Dot.h"
#include "Position.h"
#include "PropertyFactory.h"


CDot::CDot()
{
}


CDot::~CDot()
{
}


void CDot::formProperty(EPropertyType type)
{
	m_property = CPropertyFactory::getNewProperty(type);
}

bool CDot::CollideCheck(CDot& tocheck)
{
	return m_position->distanceto(*tocheck.m_position)<1;
}

bool CDot::interact(CDot& target)
{
	if (!CollideCheck(target))
		return false;
	// Do Harm to dots.
	target.m_property.harm(m_property.getHarmValue());

}
