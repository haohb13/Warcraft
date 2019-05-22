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
	, _buildWarriorTimes(0)
	{}

	virtual ~Headquarters() {	LogDebug("~Headquarters()");	}

	virtual WarriorPtr create();
	void nextWarriorType();

	template <typename Iterator>
	void setWarriorProduceOrder(Iterator beg, Iterator end) 
	{	
		for(; beg != end; ++beg) {
			_warriorProduceOrder.push_back(*beg);
		}
	}
	
	Color getColor() const {	return _color;	}

	WarriorViewPtr getWarriorView(WarriorPtr warrior) {	return _warriorViews[warrior];	}
	size_t getWarriorAmount(WARRIOR_TYPE type) {	return _warriorTypeAmounts[type]; }
	size_t getWarriorTotalAmount() const {	return _warriors.size();	}
	size_t getBuildWarriorTimes() const {	return _buildWarriorTimes;	}

protected:
	Color _color;
	size_t _elements;
	size_t _nextWarriorIndex;
	size_t _buildWarriorTimes;

	vector<WeaponPtr> _weapons;
	unordered_map<WeaponPtr, WeaponViewPtr> _weaponViews;

	vector<WarriorPtr> _warriors;
	unordered_map<WARRIOR_TYPE, size_t> _warriorTypeAmounts;

	vector<WARRIOR_TYPE> _warriorProduceOrder;
	unordered_map<WarriorPtr, WarriorViewPtr>_warriorViews;
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

class HeadquartersView
{
public:
	HeadquartersView(Headquarters * headquarters)
	: _headquarters(headquarters)
	{}

	void showStopMessage() const;
	void showWarriorAmount(WARRIOR_TYPE) const;
private:
	Headquarters * _headquarters;
};


}//end of namespace warcraft

#endif
