 ///
 /// @file    Headquarters.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 23:00:12
 ///
 
#include "Headquarters.h"
#include "Warrior.h"
#include "GameConfig.h"
#include <iostream>
using namespace std;

namespace warcraft
{
WarriorViewPtr Headquarters::getWarriorView(WarriorPtr warrior)
{	return _warriorViews[warrior];		}

WarriorPtr RedHeadquarters::create() 
{
	WARRIOR_TYPE type = _warriorProduceOrder[_nextWarriorIndex];
	WarriorPtr warrior;
	WarriorViewPtr warriorView;
	size_t id = getWarriorAmounts();
	size_t hp = GameConfig::getInstance()->warriorInitalLife(type);
	if(_elements > hp) {
		_elements -= hp;
		switch(type) {
		case ICEMAN_TYPE: 
			warrior.reset(new Iceman(_color, ++id, hp));
			warriorView.reset(new IcemanView(warrior));
			break;
		case LION_TYPE:
			warrior.reset(new Lion(_color, ++id, hp, _elements));
			warriorView.reset(new LionView(warrior));
			break;
		case WOLF_TYPE:
			warrior.reset(new Wolf(_color, ++id, hp));
			warriorView.reset(new WolfView(warrior));
			break;
		case NINJA_TYPE:
			warrior.reset(new Ninja(_color, ++id, hp));
			warriorView.reset(new NinjaView(warrior));
			break;
		case DRAGON_TYPE:
			float morale = static_cast<float>(_elements) / hp;
			warrior.reset(new Dragon(_color, ++id, hp, morale));
			warriorView.reset(new DragonView(warrior));
			break;
		}
	}

	if(warrior.get()) {
		_warriors.push_back(warrior);
		_warriorViews.insert(make_pair(warrior, warriorView));
		nextWarriorType();
	}
	return warrior;
}

void RedHeadquarters::nextWarriorType()
{	
	++_nextWarriorIndex;
	_nextWarriorIndex %= _warriorProduceOrder.size();
}

 
WarriorPtr BlueHeadquarters::create() 
{

	return nullptr;
}

void BlueHeadquarters::nextWarriorType()
{	
	++_nextWarriorIndex;
	_nextWarriorIndex %= _warriorProduceOrder.size();
}

}// end of namespace warcraft
