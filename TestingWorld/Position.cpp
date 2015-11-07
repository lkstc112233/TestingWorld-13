#include "stdafx.h"
#include "Position.h"
#include <cmath>

CPosition::CPosition()
{
}


CPosition::~CPosition()
{
}


pos_type CPosition::distanceto(CPosition &pos) const
{
	return pow(pow(getX() - pos.getX(), 2) + pow(getY() - pos.getY(), 2), 0.5);
}
