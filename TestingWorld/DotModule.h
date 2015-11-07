#pragma once
using std::shared_ptr;

#include <vector>
class CDot;

class CDotModule
{
public:
	CDotModule();
	~CDotModule();
private:
	std::vector<shared_ptr<CDot>> m_dotStorage;
public:
	void addDot(shared_ptr<CDot> dotIn);
	void interactWith(CDotModule &toInteractWith);
	inline const std::vector<shared_ptr<CDot>>& getStorage()const { return m_dotStorage; }
};

