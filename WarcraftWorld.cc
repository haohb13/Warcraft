 ///
 /// @file    WarcraftWorld.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 23:35:40
 ///
 
#include "WarcraftWorld.h"
#include "GameConfig.h"
#include "GameTime.h"
#include "Warrior.h"

#include <iostream>
using namespace std;
 
namespace warcraft
{

void WarcraftWorld::init() 
{
	_redHeadquarters = new RedHeadquarters(
		GameConfig::getInstance()->headquartersInitialElements());

	_blueHeadquarters = new BlueHeadquarters(
		GameConfig::getInstance()->headquartersInitialElements());
}

void WarcraftWorld::start() 
{	//制造武士
	bool canRedCreateWarrior = true;
	bool canBlueCreateWarrior = true;
	while(1) {
		if(canRedCreateWarrior) {
			canRedCreateWarrior = createAndShowWarrior(_redHeadquarters);
			if(!canRedCreateWarrior) {
				//....
				HeadquartersView headquartersView(_redHeadquarters);
				headquartersView.showStopMessage();
			}
		}

		if(canBlueCreateWarrior) {
			canBlueCreateWarrior = createAndShowWarrior(_blueHeadquarters);
			if(!canBlueCreateWarrior) {
				//...
				HeadquartersView headquartersView(_blueHeadquarters);
				headquartersView.showStopMessage();
			}
		}
		
		if(!canRedCreateWarrior && !canBlueCreateWarrior)
			break;
		GameTime::getInstance()->updateTime();
	}
}

bool WarcraftWorld::createAndShowWarrior(Headquarters * headquarters)
{
	WarriorPtr warrior = headquarters->create();
	if(warrior) {
		GameTime::getInstance()->showTime();
		WarriorViewPtr view = headquarters->getWarriorView(warrior);
		view->show();

		HeadquartersView headquartersView(headquarters);
		headquartersView.showWarriorAmount(warrior->getType());
		return true;
	} else {
		GameTime::getInstance()->showTime();
		return false;
	}
}
 
}// end of namespace warcraft
