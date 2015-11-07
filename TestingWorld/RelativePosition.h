#pragma once
using std::shared_ptr;
#include "Position.h"
class CRelativePosition :
	public CPosition
{
public:
	CRelativePosition();
	virtual ~CRelativePosition();
protected:
	shared_ptr<CPosition> refer;
	pos_type rad;
	ang_type alpha;
public:
	virtual void setRelativePos(shared_ptr<CPosition> pos) { refer = pos; }
	virtual void setDxDy(pos_type dx, pos_type dy);
public:
	virtual pos_type getX() const;
	virtual pos_type getY() const;
	virtual ang_type getAngle() const;
	virtual EPositionType getPositionType() { return RELATIVE_POSITION; }
};

