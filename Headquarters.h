 ///
 /// @file    Headquarters.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 20:41:56
 ///
 

#ifndef __WARCRAFT_HEADQUARTERS_H__
#define __WARCRAFT_HEADQUARTERS_H__
#include "Types.h"

#include <vector>
#include <unordered_map>
using namespace std;

namespace warcraft
{
class Weapon;
class WeaponView;
class Warrior;
class WarriorView;
class Headquarters 
{
public:

	Headquarters(Color color, size_t elements)
	: _color(color)
	, _elements(elements)
	, _nextWarriorIndex(0)
	{}

	virtual ~Headquarters() {	LogDebug("~Headquarters()");	}

	virtual WarriorPtr create();
	WeaponPtr create(WeaponType type);

	template <typename Iterator>
	void setWarriorCreatingOrder(Iterator beg, Iterator end) 
	{	
		for(; beg != end; ++beg) {
			_warriorCreatingOrder.push_back(*beg);
		}
	}
	
	Color getColor() const {	return _color;	}

	WarriorViewPtr getWarriorView(WarriorPtr warrior) {	return _warriorViews[warrior];	}
	WeaponViewPtr getWeaponView(WeaponPtr weapon) {	return _weaponViews[weapon];	}
	size_t getWarriorAmount(WarriorType type) {	return _warriorTypeAmounts[type]; }
	size_t getWarriorTotalAmount() const {	return _warriors.size();	}

private:
	void nextWarriorType();
	WarriorType getNextWarriorType() {	return _warriorCreatingOrder[_nextWarriorIndex];	}
	WarriorPtr createIceman(size_t id, size_t hp);
	WarriorPtr createLion(size_t id, size_t hp);
	WarriorPtr createWolf(size_t id, size_t hp);
	WarriorPtr createNinja(size_t id, size_t hp);
	WarriorPtr createDragon(size_t id, size_t hp);
protected:
	Color _color;
	size_t _elements;
	size_t _nextWarriorIndex;
	vector<WarriorType> _warriorCreatingOrder;

	vector<WarriorPtr> _warriors;

	unordered_map<WeaponPtr, WeaponViewPtr> _weaponViews;
	unordered_map<WarriorPtr, WarriorViewPtr>_warriorViews;
	unordered_map<WarriorType, size_t> _warriorTypeAmounts;
};

class RedHeadquarters
: public Headquarters
{
public:
	RedHeadquarters(size_t elements)
	: Headquarters(RED, elements)
	{}

	//WarriorPtr create() override;
};

class BlueHeadquarters
: public Headquarters
{
public:
	BlueHeadquarters(size_t elements)
	: Headquarters(BLUE, elements)
	{}

	//WarriorPtr create() override;

};

/***************************************************/

class HeadquartersView
{
public:
	HeadquartersView(Headquarters * headquarters)
	: _headquarters(headquarters)
	{}

	void showStopMessage() const;
	void showWarriorAmount(WarriorType) const;
private:
	Headquarters * _headquarters;
};


}//end of namespace warcraft

#endif
