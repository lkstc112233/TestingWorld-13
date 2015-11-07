#pragma once

typedef double pos_type;
typedef double ang_type;
const pos_type cellsize = 1;

enum EPositionType
{
	DIRECT_POSITION,
	RELATIVE_POSITION,
	RECTED_POSITION,
};

class CPosition
{
public:
	CPosition();
	virtual ~CPosition();
protected:
	ang_type ang = 0;
public:
	virtual pos_type getX() const = 0;
	virtual pos_type getY() const = 0;
	virtual pos_type distanceto(CPosition &pos) const;
	virtual ang_type getAngle() const { return ang; }
	virtual ang_type turn(ang_type dang) { return ang += dang; }
//	virtual void move(pos_type x, pos_type y) = 0;
	virtual EPositionType getPositionType() = 0;
	//	void optimise(){}
	//	position* getoptimisedpnt(){return null_ptr;}
};

