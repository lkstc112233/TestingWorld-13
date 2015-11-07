#pragma once
using std::shared_ptr;

#include "DotProperty.h"

class CPosition;

class CDot
{
public:
	CDot();
	~CDot();
private:
	CDotProperty m_property;
public:
	inline const CDotProperty& getProperty()const { return m_property; }
	void formProperty(EPropertyType type);
private:
	shared_ptr<CPosition> m_position;
public:
	void setPosition(shared_ptr<CPosition> position){ m_position = position; }
	bool CollideCheck(CDot& tocheck);
	CPosition& getPosition() { return *m_position; }
	bool interact(CDot& target);
};

