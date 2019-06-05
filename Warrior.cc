 ///
 /// @file    Warrior.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-20 08:16:28
 ///
 
#include "Warrior.h"
#include "Headquarters.h"

#include "Mylogger.h"
#include "GameConfig.h"

#include <sstream>
#include <iostream>
using namespace std;
 
namespace warcraft
{


void Warrior::march()
{
	size_t idx = GameConfig::getInstance()->cityCount() + 1;
	if(_color == RED) {
		if(_cityId < idx) {
			++_cityId;
			//_headquarters->increaseReachedDestinationCount();
		}
	} else {
		if(_cityId > 0) {
			--_cityId;
			//_headquarters->increaseReachedDestinationCount();
		}
	}
}

void Warrior::sentElementsToHeadquarters(size_t elements)
{
	_earnElements = elements;
	_headquarters->increaseElements(elements);
}
	

void Warrior::beRewarded()
{
	size_t elements = _headquarters->getElements();
	if(elements >= 8) {
		_hp += 8;
		_headquarters->setElements(elements - 8);
	}
}
	
void Warrior::beWinner()
{
	_headquarters->addWinner(shared_from_this());
}


void Iceman::march() 
{
	Warrior::march();
	++_steps;
	if(!(_steps % 2)) {
		if(_hp > 9) _hp -= 9;
		else _hp = 1;
		
		_forces += 20;
	}
}

void Warrior::attack(WarriorPtr warrior)
{
	size_t hp = warrior->getHp();
	if(_forces < hp) {
		warrior->setHp(hp - _forces);
	} else {
		warrior->setHp(0);
		if(warrior->getType() == LION_TYPE 
		  && _type != WOLF_TYPE) 
		{
			_hp += hp;
		}
	}
}

void Warrior::defense(WarriorPtr warrior)
{
	size_t hp = warrior->getHp();
	size_t forces = _forces / 2;
	if(forces < hp) {
		warrior->setHp(hp - forces);
	} else 
		warrior->setHp(0);
}
	
void Wolf::attack(WarriorPtr warrior)
{
	size_t hp = warrior->getHp();
	if(_forces < hp) {
		warrior->setHp(hp - _forces);
	} else {
		warrior->setHp(0);
		++_killTimes;
		if(_killTimes % 2 == 0) {
			_hp *= 2;
			_forces *= 2;
			if(warrior->getType() == LION_TYPE)
				_hp += hp;
		}
	}
}

void Ninja::defense(WarriorPtr warrior)
{ }

/**********************************/

void WarriorView::showBorn() const
{
	showName();
	printf("born\n");
}

void WarriorView::showMarch() const
{
	showName();
	printf("marched ");
	showToCity();
	showElementsAndForces();
}
	
void WarriorView::showDeath() const
{
	showName();
	printf("was killed ");
	showInCity();
	printf("\n");
}

void WarriorView::showName() const
{
	printf("%s %s %lu ",
		toString(_warrior->getClor()).c_str(),
		toString(_warrior->getType()).c_str(),
		_warrior->getId());
}
	
void WarriorView::showToCity() const
{
	printf("to city %lu ", _warrior->getCityId());
}
	
void WarriorView::showInCity() const
{
	printf("in city %lu ", _warrior->getCityId());
}

void WarriorView::showEarnElements() const
{
	showName();
	printf("earned %lu elements for his headquarter\n",
		_warrior->getEarnElements());
}

void WarriorView::showElementsAndForces() const
{
	printf("with %lu elements and force %lu\n",
		_warrior->getElements(),
		_warrior->getForces());
}

void WarriorView::showReachDestination() const
{
	showName();
	if(_warrior->getClor() == RED)
		printf("reached blue headquarter ");
	else
		printf("reached red headquarter ");
	showElementsAndForces();
}
/**********************************/
void DragonView::showWeapon() const
{
	assert(1 == _warrior->getWeapons().size());
	printf("It has a %s and it's morale is %.2f\n",
		toString(_warrior->getWeapons()[0]->getType()).c_str(),
		_warrior->getMorale());
}

void DragonView::showYell() const
{
	showName();
	printf("yelled ");
	showInCity();
	printf("\n");
}

void NinjaView::showWeapon() const
{
	assert(2 == _warrior->getWeapons().size());
	printf("It has a %s and a %s\n",
		toString(_warrior->getWeapons()[0]->getType()).c_str(),
		toString(_warrior->getWeapons()[1]->getType()).c_str());
}

void IcemanView::showWeapon() const
{
	assert(1 == _warrior->getWeapons().size());
	printf("It has a %s\n",
		toString(_warrior->getWeapons()[0]->getType()).c_str());
}

void LionView::showWeapon() const
{
	printf("It's loyalty is %lu\n", _warrior->getLoyalty());
}

void WolfView::showWeapon() const
{}
 
/**********************************/

void BattleView::showBattle() const
{
	WarriorView view1(_warrior1);
	view1.showName();
	printf("attacked ");
	WarriorView(_warrior2).showName();
	view1.showInCity();
	view1.showElementsAndForces();
}

void BattleView::showDefense() const
{
	WarriorView view2(_warrior2);
	view2.showName();
	printf("fought back against ");
	WarriorView(_warrior1).showName();
	view2.showInCity();
	printf("\n");
}

/**********************************/
}// end of namespace warcraft
