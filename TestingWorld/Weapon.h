#pragma once
#include "Entity.h"
class CRelativePosition;
class CPosition;

class CWeapon : public CEntity
{
public:
	CWeapon();
	~CWeapon();
protected:
	shared_ptr<CRelativePosition> ancher;
public:
	void setAncherTo(shared_ptr<CPosition> position);
};

