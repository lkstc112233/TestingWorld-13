#pragma once
#include "Position.h"
class CRectedPosition :
	public CPosition
{
public:
	CRectedPosition();
	virtual ~CRectedPosition();

protected:
	pos_type up;
	pos_type down;
	pos_type left;
	pos_type right;
public:
	virtual void setPos(pos_type upin, pos_type downin, pos_type leftin, pos_type rightin);
	virtual void movePos(pos_type dx, pos_type dy) { left += dx; right += dx; up += dy; down += dy; }
public:
	virtual pos_type getX() const { return (left + right) / 2; }
	virtual pos_type getY() const { return (up + down) / 2; }
	virtual EPositionType getPositionType() { return DIRECT_POSITION; }
};

