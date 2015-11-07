#include "stdafx.h"
#include "DotProperty.h"
#include "utilities.h"

CDotProperty::CDotProperty()
	:CDotProperty(PT_NOTYPE)
{
}

CDotProperty::CDotProperty(EPropertyType type)
	: dotType(type)
{
}


CDotProperty::~CDotProperty()
{
}

double CDotProperty::setHealthPoint(double hp)
{
	return changeAndReturnValue(healthPoint, hp);
}

double CDotProperty::setMaxHealthPoint(double mhp)
{
	return changeAndReturnValue(maxHealthPoint, mhp);
}

double CDotProperty::setAttack(double a)
{
	return changeAndReturnValue(attack, a);
}

double CDotProperty::setArmor(double a)
{
	return changeAndReturnValue(armor, a);
}

bool CDotProperty::isAlive()
{
	return healthPoint > 0;
}

double CDotProperty::getHarmValue()
{
	return attack;
}

double CDotProperty::harm(double damage)
{
	healthPoint -= damage * pow(0.9, armor);
	return 0.0;
}
