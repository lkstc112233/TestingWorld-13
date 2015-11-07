#include "stdafx.h"
#include "PropertyFactory.h"


CDotProperty CPropertyFactory::getNewProperty(EPropertyType type)
{
	CPropertyFormer former;
	switch(type)
	{
	case PT_DAMAGE:
		former.setType(PT_DAMAGE);
		former.setAttack(3);
		former.setArmor(5);
		break;
	case PT_GRASS:
		former.setAttack(1);
		break;
	}
	return former.formProperty();
}
