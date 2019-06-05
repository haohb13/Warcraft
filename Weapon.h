 ///
 /// @file    Weapon.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-20 07:38:31
 ///
 
#ifndef _WARCRAF_WEAPON_H
#define _WARCRAF_WEAPON_H

#include "Types.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

namespace warcraft
{

class Weapon {
public: 
	Weapon(WeaponType type, const string & name, size_t attack = 0)
	: _type(type)
	, _name(name)
	, _attack(attack)
	{}

	~Weapon() {	 /*LogDebug("~LogDebug()");	*/}

	string getName() {	return _name;	}
	size_t getAttackValue() {	return _attack;	}
	WeaponType getType() const {	return _type;	}
protected: 
	WeaponType _type;
    string _name;
    size_t _attack;
};

class Sword
: public Weapon
{
public:
	Sword(size_t attack = 0)
	: Weapon(SWORD_TYPE, "sword", attack)
	{}
};

class Bomb
: public Weapon
{
public:
	Bomb(size_t attack = 0)
	: Weapon(BOMB_TYPE, "bomb", attack)
	{}
};

class Arrow
: public Weapon
{
public:
	Arrow(size_t attack = 0)
	: Weapon(ARROW_TYPE, "arrow", attack)
	{}
};

class WeaponView
{
public:
	WeaponView(WeaponPtr weapon)
	: _weapon(weapon)
	{}
	virtual void show() const = 0;
	virtual ~WeaponView() {		/*LogDebug("~WeapView()");*/	}
protected:
	WeaponPtr _weapon;
};

class SwordView
: public WeaponView
{
public:
	SwordView(WeaponPtr weapon) 
	: WeaponView(weapon)
	{}

	void show() const
	{
		//cout << toString(_weapon->getType());
		cout << "sword";
	}
};

class BombView
: public WeaponView
{
public:
	BombView(WeaponPtr weapon) 
	: WeaponView(weapon)
	{}

	void show() const 
	{
		//cout << toString(_weapon->getType());
		cout << "bomb";
	}
};

class ArrowView 
: public WeaponView
{
public:
	ArrowView(WeaponPtr weapon) 
	: WeaponView(weapon)
	{}

	void show() const
	{
		//cout << toString(_weapon->getType());
		cout << "arrow";
	}
};

}//end of namespace warcraft
#endif //_WEAPON_H
