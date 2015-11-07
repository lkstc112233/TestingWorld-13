#pragma once
#include "DotProperty.h"

class CPropertyFactory
{
public:
	CPropertyFactory() = delete;
	~CPropertyFactory() = delete;
private:
	class CPropertyFormer
	{
	private:
		EPropertyType type = PT_NOTYPE;
		double healthPoint = 100;
		double maxHealthPoint = 100;
		double attack = 10;
		double armor = 0;
	public:
		CPropertyFormer& setType(EPropertyType pt) { type = pt; return *this; }
		CPropertyFormer& setHealthPoint(double hp) { healthPoint = hp; return *this; }
		CPropertyFormer& setMaxHealthPoint(double mhp) { maxHealthPoint = mhp; return *this; }
		CPropertyFormer& setAttack(double a) { attack = a; return *this; }
		CPropertyFormer& setArmor(double a) { armor = a; return *this; }
		CDotProperty formProperty()
		{
			CDotProperty property(type);
			property.setHealthPoint(healthPoint);
			property.setMaxHealthPoint(maxHealthPoint);
			property.setAttack(attack);
			property.setArmor(armor);
			return property;
		}
	};
public:
	static CDotProperty getNewProperty(EPropertyType type);
};

