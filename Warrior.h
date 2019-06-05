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

class Headquarters;

class Warrior 
: public std::enable_shared_from_this<Warrior>
{
public: 
	Warrior(Color color, const string & name, 
			size_t id, size_t hp, 
			size_t forces, WarriorType type)
	: _color(color)
	, _name(name)
	, _id(id)
	, _hp(hp)
	, _forces(forces)
	, _type(type)
	{}
	
	virtual ~Warrior(){	LogDebug("~Warrior"); }

	Color getClor() const {	return _color;	}
	string getName() {	return _name;	}
	size_t getId() const	{	return _id;	}
	size_t getHp() const {	return _hp;	}
	size_t getCityId() const {	return _cityId;	}
	size_t getElements() const {	return _hp;	}
	size_t getEarnElements() const {	return _earnElements;	}
	size_t getForces() const {	return _forces;	}
	WarriorType getType() const {	return _type;	}
	
		
	virtual float getMorale() const {	return 0;	} 
	virtual size_t getLoyalty() const {	return 0;	}
	virtual void march();
	virtual void attack(WarriorPtr warrior);
	virtual void defense(WarriorPtr warrior);

	const vector<WeaponPtr> & getWeapons() const {	return _weapons;	}	
	void setWeapon(WeaponPtr weapon) { _weapons.push_back(weapon); }

	void setHp(size_t hp) {	_hp = hp; }
	void setCity(size_t id) {	_cityId = id;	}
	void setHeadquarters(Headquarters * headquarters) {	_headquarters = headquarters;	}
	void sentElementsToHeadquarters(size_t elements);

	void beRewarded();
	void beWinner();

protected: 
	Color _color;
	string _name;
	size_t _id;
	size_t _hp;
	size_t _cityId;
	size_t _forces;
	size_t _earnElements;
	WarriorType _type;
	vector<WeaponPtr> _weapons;
	Headquarters * _headquarters;
};

class Dragon
: public Warrior
{
public:
	Dragon(Color color, size_t id, size_t hp, size_t forces, float morale)
	: Warrior(color, "dragon", id, hp, forces,DRAGON_TYPE)
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
	Ninja(Color color, size_t id, size_t hp, size_t forces)
	: Warrior(color, "ninja", id, hp, forces, NINJA_TYPE)
	{}

	virtual void defense(WarriorPtr warrior) override;
};

class Iceman
: public Warrior
{
public:
	Iceman(Color color, size_t id, size_t hp, size_t forces)
	: Warrior(color, "iceman", id, hp, forces, ICEMAN_TYPE)
	, _steps(0)
	{}

	void march() override;

private: 
	size_t _steps;
};

class Lion
: public Warrior
{
public:
	Lion(Color color, size_t id, size_t hp, size_t forces, size_t loyalty)
	: Warrior(color, "lion", id, hp, forces, LION_TYPE)
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
	Wolf(Color color, size_t id, size_t hp, size_t forces)
	: Warrior(color, "wolf", id, hp, forces, WOLF_TYPE)
	, _killTimes(0)
	{}
	
	void attack(WarriorPtr warrior) override;

private:
	int _killTimes;
};

/******************************************/

class WarriorView
{
public:
	WarriorView(WarriorPtr warrior)
	: _warrior(warrior)
	{}

	virtual ~WarriorView() {}
	//virtual void show() const;
	void showBorn() const;
	void showMarch() const;
	void showEarnElements() const;
	void showName() const;
	void showToCity() const;
	void showInCity() const;
	void showDeath() const;
	void showElementsAndForces() const;
	void showReachDestination() const;
	virtual void showWeapon() const{}
private:

protected:
	WarriorPtr _warrior;
};

/******************************************/
class DragonView
: public WarriorView
{
public:
	DragonView(WarriorPtr warrior)
	: WarriorView(warrior)
	{}

	//void show() const;
	void showWeapon() const;
	void showYell() const;
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

class BattleView
{
public:
	BattleView(WarriorPtr warrior1, WarriorPtr warrior2)
	: _warrior1(warrior1)
	, _warrior2(warrior2)
	{}

	void showBattle() const;
	void showDefense() const;
private:
	WarriorPtr _warrior1;
	WarriorPtr _warrior2;
};

}//end of namespace warcraft

#endif //_WARRIOR_H
