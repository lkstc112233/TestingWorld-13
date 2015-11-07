#include "stdafx.h"
#include "RectedPosition.h"


CRectedPosition::CRectedPosition()
{
}


CRectedPosition::~CRectedPosition()
{
}

void CRectedPosition::setPos(pos_type upin, pos_type downin, pos_type leftin, pos_type rightin)
{
	if (upin < downin)
	{
		up = downin;
		down = upin;
	}
	else
	{
		up = upin;
		down = downin;
	}
	if (leftin > rightin)
	{
		right = leftin;
		left = rightin;
	}
	else
	{
		left = leftin;
		right = rightin;
	}
}
