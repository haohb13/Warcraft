 ///
 /// @file    Weapon.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-20 08:01:39
 ///
#ifndef __WARCRAFT_WARRIOR_H__
#define __WARCRAFT_WARRIOR_H__

#include "Mylogger.h"
#include "Types.h"
#include "Weapon.h"

#include <vector>
using std::vector;

namespace warcraft 
{

class Warrior {
public: 
	Warrior(Color color, const string & name, size_t id, size_t hp, WarriorType type)
	: _color(color)
	, _name(name)
	, _id(id)
	, _hp(hp)
	, _type(type)
	{}
	
	virtual ~Warrior(){	LogDebug("~Warrior"); }

	Color getClor() const {	return _color;	}
	string getName() {	return _name;	}
	size_t getId() const	{	return _id;	}
	size_t getHp() const {	return _hp;	}
	WarriorType getType() const {	return _type;	}
		
	virtual float getMorale() const {	return 0;	} 
	virtual size_t getLoyalty() const {	return 0;	}

	const vector<WeaponPtr> & getWeapons() const {	return _weapons;	}	
	void setWeapon(WeaponPtr weapon) { _weapons.push_back(weapon); }

protected: 
	Color _color;
	string _name;
	size_t _id;
	size_t _hp;
	WarriorType _type;
	vector<WeaponPtr> _weapons;
};

class Dragon
: public Warrior
{
public:
	Dragon(Color color, size_t id, size_t hp, float morale)
	: Warrior(color, "dragon", id, hp, DRAGON_TYPE)
	, _morale(morale)
	{}

	virtual 
	float getMorale() const  {	return _morale;	}

private:
	float _morale;
};

class Ninja
: public Warrior
{
public:
	Ninja(Color color, size_t id, size_t hp)
	: Warrior(color, "ninja", id, hp, NINJA_TYPE)
	{}
};

class Iceman
: public Warrior
{
public:
	Iceman(Color color, size_t id, size_t hp)
	: Warrior(color, "iceman", id, hp, ICEMAN_TYPE)
	{}
};

class Lion
: public Warrior
{
public:
	Lion(Color color, size_t id, size_t hp, size_t loyalty)
	: Warrior(color, "lion", id, hp, LION_TYPE)
	, _loyalty(loyalty)
	{}

	virtual
	size_t getLoyalty() const override {	return _loyalty;	}	

private:
	size_t _loyalty;
};

class Wolf
: public Warrior
{
public:
	Wolf(Color color, size_t id, size_t hp)
	: Warrior(color, "wolf", id, hp, WOLF_TYPE)
	{}
};

/******************************************/

class WarriorView
{
public:
	WarriorView(WarriorPtr warrior)
	: _warrior(warrior)
	{}

	virtual ~WarriorView() {}
	virtual void show() const;
	virtual void showWeapon() const = 0;

protected:
	WarriorPtr _warrior;
};

class DragonView
: public WarriorView
{
public:
	DragonView(WarriorPtr warrior)
	: WarriorView(warrior)
	{}

	//void show() const;
	void showWeapon() const;

};

class NinjaView
: public WarriorView
{
public:
	NinjaView(WarriorPtr warrior)
	: WarriorView(warrior)
	{}

	//void show() const;
	void showWeapon() const;
};


class IcemanView
: public WarriorView
{
public:
	IcemanView(WarriorPtr warrior)
	: WarriorView(warrior)
	{}

	//void show() const;
	void showWeapon() const;

};

class LionView 
: public WarriorView
{
public:
	LionView(WarriorPtr warrior)
	: WarriorView(warrior)
	{}

	//void show() const;
	void showWeapon() const;
};

class WolfView
: public WarriorView
{
public:
	WolfView(WarriorPtr warrior)
	: WarriorView(warrior)
	{}

	//void show() const;
	void showWeapon() const;

};

}//end of namespace warcraft

#endif //_WARRIOR_H
