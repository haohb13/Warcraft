 ///
 /// @file    Types.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 20:04:16
 ///
 
#ifndef _WARCRAFT_COLOR_H_
#define _WARCRAFT_COLOR_H_
#include <memory>
#include "Mylogger.h"

namespace warcraft
{
 
enum Color { 
	RED, 
	BLUE 
};

enum WARRIOR_TYPE { 
	DRAGON_TYPE, 
	NINJA_TYPE, 
	ICEMAN_TYPE, 
	LION_TYPE, 
	WOLF_TYPE 
};

enum WeaponType { 
	SWORD_TYPE, 
	BOMB_TYPE, 
	ARROW_TYPE 
};

class Warrior;
class WarriorView;
class Weapon;
class WeaponView;

using std::shared_ptr;

using WarriorPtr = shared_ptr<Warrior>;
using WarriorViewPtr = shared_ptr<WarriorView>;
using WeaponPtr = shared_ptr<Weapon>;
using WeaponViewPtr = shared_ptr<WeaponView>;
}//end of namespace warcraft
#endif
