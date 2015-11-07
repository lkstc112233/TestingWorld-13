#pragma once
#include <vector>
#include "Entity.h"

class CWeapon;

class CCharacter : public CEntity
{
public:
	CCharacter();
	~CCharacter();
protected:
	std::vector<shared_ptr<CWeapon>> equipedWeapon;
public:
	inline const std::vector<shared_ptr<CWeapon>> getEquipedWeapon() const { return equipedWeapon; }
};

