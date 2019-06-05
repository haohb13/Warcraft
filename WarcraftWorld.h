 ///
 /// @file    WarcraftWorld.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 20:39:58
 ///
 

#ifndef __WARCRAFT_WARCRAFTWORLD_H__ 
#define __WARCRAFT_WARCRAFTWORLD_H__ 

#include "Headquarters.h"
#include "City.h"
#include <stdio.h>

namespace warcraft
{

class City;

class WarcraftWorld
{
public:
	explicit
	WarcraftWorld()
	: _redHeadquarters(nullptr)
	, _blueHeadquarters(nullptr)
	{	init();	}

	~WarcraftWorld() 
	{	
		if(_redHeadquarters) delete _redHeadquarters;
		if(_blueHeadquarters) delete _blueHeadquarters;
	}

	void start();

	template <typename Iterator>
	void setRedWarriorCreatingOrder(Iterator beg, Iterator end);

	template <typename Iterator>
	void setBlueWarriorCreatingOrder(Iterator beg, Iterator end);
private:
	void init();
	//------------事件begin-----------
	void createWarrior();
	bool warriorMarch();
	void cityProduceElements();
	void takeCityElements();
	void battle();
	void headquartersReportElements();

	//------------事件end ------------

	bool createWarrior(Headquarters *);
	void warriorMarch(Headquarters * headquarters);
	bool checkRedHeadquartersBeTaken();
	bool checkBlueHeadquartersBeTaken();

	//void showStopCreatingMessage(Headquarters * headquarters);
	
private:
	Headquarters * _redHeadquarters;
	Headquarters * _blueHeadquarters;
	vector<City> _cities;
};

template <typename Iterator>
void WarcraftWorld::setRedWarriorCreatingOrder(Iterator beg, Iterator end)
{
	_redHeadquarters->setWarriorCreatingOrder(beg, end);
}

template <typename Iterator>
void WarcraftWorld::setBlueWarriorCreatingOrder(Iterator beg, Iterator end)
{
	_blueHeadquarters->setWarriorCreatingOrder(beg, end);
}
}//end of namespace warcraft
 
#endif
