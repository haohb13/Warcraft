 ///
 /// @file    WarcraftWorld.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 23:35:40
 ///
 
#include "WarcraftWorld.h"
#include "GameConfig.h"
#include "GameTime.h"
#include "Warrior.h"

#include <unistd.h>

#include <iostream>
using namespace std;
 
namespace warcraft
{

void WarcraftWorld::init() 
{
	_redHeadquarters = new RedHeadquarters(
		GameConfig::getInstance()->headquartersInitialElements());
	_redHeadquarters->setId(0);

	_blueHeadquarters = new BlueHeadquarters(
		GameConfig::getInstance()->headquartersInitialElements());

	size_t sz = GameConfig::getInstance()->cityCount() + 2;
	_blueHeadquarters->setId(sz - 1);

	_cities.reserve(sz);
	for(size_t idx = 0; idx != sz; ++idx) {
		_cities.push_back(City(idx));
	}
}

void WarcraftWorld::start()
{
	while(1) {
		createWarrior();
		if(!warriorMarch())
		{	break; }
		cityProduceElements();
		takeCityElements();
		battle();
		headquartersReportElements();
		//sleep(3);
	}
}

void WarcraftWorld::createWarrior() 
{	//制造武士
	//cout << "create Warrior enter() ..." << endl;
	bool canRedCreateWarrior = true;
	bool canBlueCreateWarrior = true;
	if(canRedCreateWarrior) {
		canRedCreateWarrior = createWarrior(_redHeadquarters);
	}

	if(canBlueCreateWarrior) {
		canBlueCreateWarrior = createWarrior(_blueHeadquarters);
	}
	GameTime::getInstance()->updateTime();
	//cout << "create Warrior after() ..." << endl;
}

//return true, game go on 
//return false game over
bool WarcraftWorld::warriorMarch()
{
	warriorMarch(_redHeadquarters);
	warriorMarch(_blueHeadquarters);

	//检查红魔军司令部所在的城市
	if(checkRedHeadquartersBeTaken())
		return false;

	size_t sz = _cities.size();
	for(size_t idx = 1; idx != sz - 1; ++idx) {
		auto & warriors1 = _cities[idx].getRedWarriors();
		for(auto & warrior : warriors1) {
			GameTime::getInstance()->showTime();
			WarriorView(warrior).showMarch();
		}

		auto & warriors2 = _cities[idx].getBlueWarriors();
		for(auto & warrior : warriors2) {
			GameTime::getInstance()->showTime();
			WarriorView(warrior).showMarch();
		}
	}
	
	//检查蓝魔军司令部所在的城市
	if(checkBlueHeadquartersBeTaken())
		return false;

	GameTime::getInstance()->updateTime();
	return true;
}

void WarcraftWorld::cityProduceElements()
{
	size_t sz = _cities.size();
	for(size_t idx = 1; idx != sz - 1; ++idx) {
		_cities[idx].produceElements();
	}
	GameTime::getInstance()->updateTime();
}

void WarcraftWorld::takeCityElements()
{
	size_t sz = _cities.size();
	for(size_t idx = 1; idx != sz - 1; ++idx) {
		if(_cities[idx].getWarriorAmount() == 1) {
			WarriorPtr warrior = _cities[idx].getSoloWarrior();
			_cities[idx].takenBy(warrior);
			GameTime::getInstance()->showTime();
			WarriorView(warrior).showEarnElements();;
		}
	}
	GameTime::getInstance()->updateTime();
}

void WarcraftWorld::battle()
{
	size_t sz = _cities.size();
	for(size_t idx = 1; idx != sz - 1; ++idx) {
		if(_cities[idx].getWarriorAmount() == 2) {
			_cities[idx].startBattle();
		}
	}

	_redHeadquarters->reward();
	_blueHeadquarters->reward();

	GameTime::getInstance()->updateTime();
}

void WarcraftWorld::headquartersReportElements()
{
	GameTime::getInstance()->showTime();
	HeadquartersView(_redHeadquarters).showLeftElements();
	GameTime::getInstance()->showTime();
	HeadquartersView(_blueHeadquarters).showLeftElements();
	GameTime::getInstance()->updateTime();
}

void WarcraftWorld::warriorMarch(Headquarters * headquarters)
{
	auto & warriors = headquarters->getWarriors();
	for(auto & warrior : warriors) {
		if(warrior->getHp() > 0) {// 还存活的warrior前进
			_cities[warrior->getCityId()].detach(warrior);
			warrior->march();
			_cities[warrior->getCityId()].attach(warrior);
		}
	}
}

bool WarcraftWorld::createWarrior(Headquarters * headquarters)
{
	WarriorPtr warrior = headquarters->create();
	if(warrior) {
		warrior->setHeadquarters(headquarters);
		GameTime::getInstance()->showTime();
		WarriorView(warrior).showBorn();

		return true;
	} else {
		return false;
	}
}

bool WarcraftWorld::checkRedHeadquartersBeTaken()
{
	auto & warriors = _cities[0].getBlueWarriors();
	size_t sz = warriors.size();
	if(sz == 0)
		return false;
	else if(sz == 1) {
		GameTime::getInstance()->showTime();
		WarriorView(warriors[0]).showReachDestination();
		return false;
	} else if(sz == 2) {
		GameTime::getInstance()->showTime();
		WarriorView(warriors[1]).showReachDestination();
		GameTime::getInstance()->showTime();
		HeadquartersView(_redHeadquarters).showBeTaken();
		return true;
	}
}

bool WarcraftWorld::checkBlueHeadquartersBeTaken()
{
	auto & warriors = _cities[_cities.size() - 1].getRedWarriors();
	size_t sz = warriors.size();
	//cout << " blue headquarters taken sz = " << sz << endl;
	if(sz == 0) 
		return false;
	else if(sz == 1) {
		GameTime::getInstance()->showTime();
		WarriorView(warriors[0]).showReachDestination();
		return false;
	} else if(sz == 2) {
		GameTime::getInstance()->showTime();
		WarriorView(warriors[1]).showReachDestination();
		GameTime::getInstance()->showTime();
		HeadquartersView(_blueHeadquarters).showBeTaken();
		return true;
	} 
}

//void WarcraftWorld::showStopCreatingMessage(Headquarters * headquarters)
//{
//	GameTime::getInstance()->showTime();
//	HeadquartersView headquartersView(headquarters);
//	headquartersView.showStopMessage();
//}
 
}// end of namespace warcraft
