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

WarriorPtr Headquarters::create() 
{
	WarriorType type = getNextWarriorType();
	WarriorPtr warrior;
	WarriorViewPtr warriorView;
	WeaponPtr weapon;
	size_t id = getWarriorTotalAmount();
	size_t hp = GameConfig::getInstance()->warriorInitalLife(type);
	while(_elements > 0) {
		if(_elements < hp) { //生命元不足以制造当前武士时，就试图制造下一个
			nextWarriorType();
			WarriorType nextType = getNextWarriorType();
			hp = GameConfig::getInstance()->warriorInitalLife(nextType);
			if(nextType != type) continue;
			else break;
		} else {
			_elements -= hp;
			switch(type) {
			case ICEMAN_TYPE: 
				warrior = createDragon(++id, hp);
				warriorView.reset(new IcemanView(warrior));
				break;
			case LION_TYPE:
				warrior = createLion(++id, hp);
				warriorView.reset(new LionView(warrior));
				break;
			case WOLF_TYPE:
				warrior = createWolf(++id, hp);
				warriorView.reset(new WolfView(warrior)); 
				break;
			case NINJA_TYPE:
				warrior = createNinja(++id, hp);
				warriorView.reset(new NinjaView(warrior));
				break;
			case DRAGON_TYPE:
				warrior = createDragon(++id, hp);
				warriorView.reset(new DragonView(warrior));
				break;
			default:break;
			}
			break;
		} 
	}

	if(warrior.get()) {
		_warriors.push_back(warrior);
		_warriorViews.insert(make_pair(warrior, warriorView));
		++_warriorTypeAmounts[type];
		nextWarriorType();
	}
	return warrior;
}

WarriorPtr Headquarters::createIceman(size_t id, size_t hp)
{	
	//1把武器
	WarriorPtr warrior(new Iceman(_color, id, hp));
	WeaponPtr weapon = create(static_cast<WeaponType>(id % 3));
	warrior->setWeapon(weapon);
	return warrior;
}

WarriorPtr Headquarters::createLion(size_t id, size_t hp)
{
	//无武器, 有忠诚度
	WarriorPtr warrior(new Lion(_color, id, hp, _elements));
	return warrior;
}

WarriorPtr Headquarters::createWolf(size_t id, size_t hp)
{	
	//无武器 (无特点)
	WarriorPtr warrior(new Wolf(_color, ++id, hp));
	return warrior;
}

WarriorPtr Headquarters::createNinja(size_t id, size_t hp)
{
	//2把武器
	WarriorPtr warrior(new Ninja(_color, id, hp));
	WeaponPtr weapon = create(static_cast<WeaponType>(id % 3));
	warrior->setWeapon(weapon);

	weapon = create(static_cast<WeaponType>((id + 1) % 3));
	warrior->setWeapon(weapon);
	return warrior;
}

WarriorPtr Headquarters::createDragon(size_t id, size_t hp)
{	
	//1把武器, 有士气
	float morale = static_cast<float>(_elements) / hp;
	WarriorPtr warrior(new Dragon(_color, id, hp, morale));
	WeaponPtr weapon = create(static_cast<WeaponType>(id % 3));
	warrior->setWeapon(weapon);
	return warrior;
}

WeaponPtr Headquarters::create(WeaponType type)
{
	WeaponPtr weapon;
	WeaponViewPtr weaponView;
	switch(type) {
	case SWORD_TYPE: 
		weapon.reset(new Sword()); 
		weaponView.reset(new SwordView(weapon));
		break;
	case BOMB_TYPE: 
		weapon.reset(new Bomb());
		weaponView.reset(new BombView(weapon));
		break;
	case ARROW_TYPE: 
		weapon.reset(new Arrow()); 
		weaponView.reset(new ArrowView(weapon));
		break;
	default:break;
	}
	_weaponViews.insert(std::make_pair(weapon, weaponView));

	return weapon;
}

void Headquarters::nextWarriorType()
{	
	++_nextWarriorIndex;
	_nextWarriorIndex %= _warriorCreatingOrder.size();
}

/*********************************************************************/

void HeadquartersView::showWarriorAmount(WarriorType type) const
{
	cout << _headquarters->getWarriorAmount(type)
		 << " " << toString(type) << " in " 
		 << toString(_headquarters->getColor()) 
		 << " headquarter" << endl;
}

void HeadquartersView::showStopMessage() const
{
	cout << toString(_headquarters->getColor())
		 << " headquarter stops making warriors" << endl;
}

}// end of namespace warcraft
