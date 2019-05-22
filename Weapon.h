 ///
 /// @file    Weapon.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-20 07:38:31
 ///
 
#ifndef _WARCRAF_WEAPON_H
#define _WARCRAF_WEAPON_H

#include "Types.h"
#include <string>
using std::string;

namespace warcraft
{

class Weapon {
public: 
	Weapon(const string & name, size_t attack)
	: _name(name)
	, _attack(attack)
	{}

	~Weapon() {	LogDebug("~LogDebug()");	}

	string name() {	return _name;	}
	size_t getAttackValue() {	return _attack;	}
protected: 
    string _name;
    size_t _attack;
};

class WeaponView
{
public:
	virtual void show() const;
	virtual ~WeaponView() {		LogDebug("~WeapView()");	}
};

}//end of namespace warcraft
#endif //_WEAPON_H
