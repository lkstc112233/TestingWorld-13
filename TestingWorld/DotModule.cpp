#include "stdafx.h"
#include "DotModule.h"
#include "Dot.h"


CDotModule::CDotModule()
{
}


CDotModule::~CDotModule()
{
}

void CDotModule::addDot(shared_ptr<CDot> dotIn)
{
	m_dotStorage.push_back(dotIn);
}

void CDotModule::interactWith(CDotModule & toInteractWith)
{
	for (auto subjectDotPointer : m_dotStorage)
	{
		for (auto objectDotPointer : toInteractWith.m_dotStorage)
		{
			subjectDotPointer->interact(*objectDotPointer);
		}
	}
}
