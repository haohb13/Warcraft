 ///
 /// @file    City.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-28 21:37:52
 ///
 
#include "City.h"
#include "Warrior.h"
#include "GameTime.h"
#include <algorithm>
#include <iostream>
using namespace std;

namespace warcraft
{

void City::takenBy(WarriorPtr warrior)
{
	warrior->sentElementsToHeadquarters(_elements);
	_elements = 0;
}


void City::attach(WarriorPtr warrior)
{
	if(warrior->getClor() == RED) {
		auto it = find(_redWarriors.begin(), _redWarriors.end(), warrior);
		if(it == _redWarriors.end())
			_redWarriors.push_back(warrior);
	} else {
		auto it = find(_blueWarriors.begin(), _blueWarriors.end(), warrior);
		if(it == _blueWarriors.end())
			_blueWarriors.push_back(warrior);
	}
}

void City::detach(WarriorPtr warrior)
{
	if(warrior->getClor() == RED) {
		auto it = find(_redWarriors.begin(), _redWarriors.end(), warrior);
		if(it != _redWarriors.end())
			_redWarriors.erase(it);
	} else {
		auto it = find(_blueWarriors.begin(), _blueWarriors.end(), warrior);
		if(it != _blueWarriors.end())
			_blueWarriors.erase(it);
	}
}

void City::produceElements()
{
	_elements += 10;
}

void City::startBattle()
{
	assert(getWarriorAmount() == 2);
	if(_flag == RED || _id % 2) {
		battle(_redWarriors[0], _blueWarriors[0]);
	} else if(_flag == BLUE || !(_id % 2)){
		battle(_blueWarriors[0], _redWarriors[0]);
	}
}

void City::battle(WarriorPtr warrior1, WarriorPtr warrior2)
{
	GameTime::getInstance()->showTime();
	BattleView view(warrior1, warrior2);
	view.showBattle();

	warrior1->attack(warrior2);
	if(warrior2->getHp() == 0) {// warrior2被杀死
		warrior1->beWinner();
		GameTime::getInstance()->showTime();
		WarriorView(warrior2).showDeath();
		detach(warrior2);
		takenBy(warrior1);//取走城市的生命元

		GameTime::getInstance()->showTime();
		WarriorView(warrior1).showEarnElements();
		//是否插旗子
		if(isChangingFlag(warrior1)) {
			GameTime::getInstance()->showTime();
			CityView(this).showFlag();
		}

	} else if(warrior2->getHp() > 0) {// warrior2反击
		if(warrior2->getType() != NINJA_TYPE) {
			GameTime::getInstance()->showTime();
			view.showDefense();
			warrior2->defense(warrior1);

			if(warrior1->getHp() == 0) {
				warrior2->beWinner();
				GameTime::getInstance()->showTime();
				WarriorView(warrior1).showDeath();
				detach(warrior1);
				takenBy(warrior2);

				GameTime::getInstance()->showTime();
				WarriorView(warrior2).showEarnElements();
				//是否插旗子
				if(isChangingFlag(warrior2)) {
					GameTime::getInstance()->showTime();
					CityView(this).showFlag();
				}
			}
		}
	}

	if((warrior1->getType() == DRAGON_TYPE) &&
		warrior1->getHp() > 0) {
		GameTime::getInstance()->showTime();
		DragonView(warrior1).showYell();
	}
}
	
bool City::isChangingFlag(WarriorPtr warrior)
{
	if(_flag == NOTSET) {
		if(warrior->getClor() == RED) {
			++_redWinCount;
			if(_redWinCount == 2) {
				_flag = RED;
				return true;
			}
			if(_blueWinCount == 1) {
				_blueWinCount = 0;
			}
			return false;
		} else {
			++_blueWinCount;
			if(_blueWinCount == 2) {
				_flag = BLUE;
				return true;
			}
			if(_redWinCount == 1) {
				_redWinCount = 0;
			}
			return false;
		}
	} else if(_flag == RED) {
		if(warrior->getClor() == BLUE) {
			++_blueWinCount;
			_redWinCount = 0;
			if(_blueWinCount == 2) {
				_flag = BLUE;
				return true;
			}
		}
		return false;
	} else if(_flag == BLUE) {
		if(warrior->getClor() == RED) {
			++_redWinCount;
			_blueWinCount = 0;
			if(_redWinCount == 2) {
				_flag = RED;
				return true;
			}
		}
		return false;
	} else
		return false;
}

/**************************************************/

void CityView::showFlag() const 
{
	if(_city->getFlag() == RED)
		printf("red flag raised in city %lu\n", _city->getId());
	else if(_city->getFlag() == BLUE)
		printf("blue flag raised in city %lu\n", _city->getId());
}

}//end of namespace warcraft
