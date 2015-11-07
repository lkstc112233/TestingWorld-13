#include "stdafx.h"
#include "RelativePosition.h"
#include "utilities.h"
#include <cmath>

CRelativePosition::CRelativePosition()
{
}


CRelativePosition::~CRelativePosition()
{
}

pos_type CRelativePosition::getX() const
{
	return refer->getX() + rad * sin(refer->getAngle() + alpha);
}

pos_type CRelativePosition::getY() const
{
	return refer->getY() + rad * cos(refer->getAngle() + alpha);
}

pos_type CRelativePosition::getAngle() const
{
	return refer->getAngle() + alpha+ang;
}

void CRelativePosition::setDxDy(pos_type dx, pos_type dy)
{
	rad = pow(pow(dx, 2) + pow(dy, 2), 0.5);
	alpha = asin(dx/rad);
	if (dy < 0)
		alpha = PI - alpha;
}