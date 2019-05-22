 ///
 /// @file    WarcraftWorld.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 20:39:58
 ///
 

#ifndef __WARCRAFT_WARCRAFTWORLD_H__ 
#define __WARCRAFT_WARCRAFTWORLD_H__ 

#include "Headquarters.h"
#include <stdio.h>

namespace warcraft
{

class Headquarters;

class WarcraftWorld
{
public:
	explicit
	WarcraftWorld(size_t groupId = 0)
	: _redHeadquarters(nullptr)
	, _blueHeadquarters(nullptr)
	{	init();	}

	~WarcraftWorld() {	
		if(_redHeadquarters) delete _redHeadquarters;
		if(_blueHeadquarters) delete _blueHeadquarters;
	}

	void init();
	void start();

	template <typename Iterator>
	void setRedWarriorProduceOrder(Iterator beg, Iterator end);

	template <typename Iterator>
	void setBlueWarriorProduceOrder(Iterator beg, Iterator end);


private:
	Headquarters * _redHeadquarters;
	Headquarters * _blueHeadquarters;
	//Cities;
};

template <typename Iterator>
void WarcraftWorld::setRedWarriorProduceOrder(Iterator beg, Iterator end)
{
	_redHeadquarters->setWarriorProduceOrder(beg, end);
}

template <typename Iterator>
void WarcraftWorld::setBlueWarriorProduceOrder(Iterator beg, Iterator end)
{
	_blueHeadquarters->setWarriorProduceOrder(beg, end);
}
}//end of namespace warcraft
 
#endif
