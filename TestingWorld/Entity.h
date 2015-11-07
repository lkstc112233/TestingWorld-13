#pragma once
using std::shared_ptr;

class CDotModule;

class CEntity
{
public:
	CEntity();
	virtual ~CEntity();
protected:
	shared_ptr<CDotModule> m_module;
public:
	CDotModule& getModule() { return *m_module; }
	void setModule(shared_ptr<CDotModule> module);

};

