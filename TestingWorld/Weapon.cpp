#include "stdafx.h"
#include "Weapon.h"

#include "RelativePosition.h"

CWeapon::CWeapon()
{
}


CWeapon::~CWeapon()
{
}

void CWeapon::setAncherTo(shared_ptr<CPosition> position)
{
	ancher->setRelativePos(position);
}
