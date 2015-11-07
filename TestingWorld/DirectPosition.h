#pragma once
#include "Position.h"
class CDirectPosition :
	public CPosition
{
public:
	CDirectPosition();
	virtual ~CDirectPosition();
protected:
	pos_type x;
	pos_type y;
public:
	virtual void setPos(pos_type xin, pos_type yin) { x = xin; y = yin; }
	virtual void movePos(pos_type dx, pos_type dy){ x += dx; y += dy; }
public:
	virtual pos_type getX() const { return x; }
	virtual pos_type getY() const { return y; }
	virtual EPositionType getPositionType() { return DIRECT_POSITION; }
};

