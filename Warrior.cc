 ///
 /// @file    Warrior.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-20 08:16:28
 ///
 
#include "Warrior.h"

#include "Mylogger.h"

#include <sstream>
#include <iostream>
using namespace std;
 
namespace warcraft
{

/**********************************/

void WarriorView::show() const
{
	printf("%s %s %lu born with strength %lu,",
		toString(_warrior->getClor()).c_str(),
		toString(_warrior->getType()).c_str(),
		_warrior->getId(),
	    _warrior->getHp());
}

/**********************************/

void DragonView::showWeapon() const
{
	assert(1 == _warrior->getWeapons().size());
	printf("It has a %s and it's morale is %.2f\n",
		toString(_warrior->getWeapons()[0]->getType()).c_str(),
		_warrior->getMorale());
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
}// end of namespace warcraft
