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
WarriorView * Headquarters::getWarriorView(Warrior * warrior)
{	return _views[warrior];		}

Warrior * RedHeadquarters::create() 
{
	WARRIOR_TYPE type = _warriorProduceOrder[_nextWarriorIndex];
	Warrior * warrior = nullptr;
	WarriorView * view = nullptr;
	size_t id = getWarriorAmounts();
	size_t hp = GameConfig::getInstance()->warriorInitalLife(type);
	if(_elements > hp) {
		_elements -= hp;
		switch(type) {
		case ICEMAN_TYPE: 
			warrior = new Iceman(_color, ++id, hp);
			view = new IcemanView(warrior);
			break;
		case LION_TYPE:
			warrior = new Lion(_color, ++id, hp, _elements);
			view = new LionView(warrior);
			break;
		case WOLF_TYPE:
			warrior = new Wolf(_color, ++id, hp);
			view = new WolfView(warrior);
			break;
		case NINJA_TYPE:
			warrior = new Ninja(_color, ++id, hp);
			view = new NinjaView(warrior);
			break;
		case DRAGON_TYPE:
			float morale = static_cast<float>(_elements) / hp;
			warrior = new Dragon(_color, ++id, hp, morale);
			view = new DragonView(warrior);
			break;
		}
	}

	if(warrior) {
		_warriors.push_back(warrior);
		_views.insert(make_pair(warrior, view));
		nextWarriorType();
	}
	return warrior;
}

void RedHeadquarters::nextWarriorType()
{	
	++_nextWarriorIndex;
	_nextWarriorIndex %= _warriorProduceOrder.size();
}

 
Warrior * BlueHeadquarters::create() 
{

}

void BlueHeadquarters::nextWarriorType()
{	
	++_nextWarriorIndex;
	_nextWarriorIndex %= _warriorProduceOrder.size();
}

}// end of namespace warcraft
