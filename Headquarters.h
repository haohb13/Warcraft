 ///
 /// @file    Headquarters.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 20:41:56
 ///
 

#ifndef __WARCRAFT_HEADQUARTERS_H__
#define __WARCRAFT_HEADQUARTERS_H__
#include "Types.h"
#include "Warrior.h"

#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;


namespace warcraft
{

struct WarriorComparator
{
	bool operator()(const WarriorPtr & lhs, const WarriorPtr & rhs) const
	{
		if(lhs->getClor() == RED ) 
			return lhs->getCityId() < rhs->getCityId();
		else 
			return lhs->getCityId() > rhs->getCityId();
	}
};

class Headquarters 
{
public:

	Headquarters(Color color, size_t elements)
	: _color(color)
	, _elements(elements)
	, _earnElements(0)
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
	
	size_t getId() const {	return _id;	}
	void setId(size_t id) {	_id = id;	}
	Color getColor() const {	return _color;	}
	size_t getElements() const {	return _elements;	}
	void setElements(size_t elements) {	_elements = elements;	}

	vector<WarriorPtr> & getWarriors() {	return _warriors;	}

	//WarriorViewPtr getWarriorView(WarriorPtr warrior) {	return _warriorViews[warrior];	}
	//WeaponViewPtr getWeaponView(WeaponPtr weapon) {	return _weaponViews[weapon];	}
	size_t getWarriorAmount(WarriorType type) {	return _warriorTypeAmounts[type]; }
	size_t getWarriorTotalAmount() const {	return _warriors.size();	}

	void increaseElements(size_t elements) { _earnElements += elements;}
	void addWinner(WarriorPtr warrior) {	_winners.push(warrior);	}
	void reward();

private:
	void nextWarriorType();
	WarriorType getNextWarriorType() {	return _warriorCreatingOrder[_nextWarriorIndex];	}
	WarriorPtr createIceman(size_t id, size_t hp, size_t forces);
	WarriorPtr createLion(size_t id, size_t hp, size_t forces);
	WarriorPtr createWolf(size_t id, size_t hp, size_t forces);
	WarriorPtr createNinja(size_t id, size_t hp, size_t forces);
	WarriorPtr createDragon(size_t id, size_t hp, size_t forces);
protected:
	Color _color;
	size_t _id;
	size_t _elements;
	size_t _earnElements;
	size_t _nextWarriorIndex;
	//size_t _reachedDestinationCount;
	vector<WarriorType> _warriorCreatingOrder;

	priority_queue<WarriorPtr, vector<WarriorPtr>, WarriorComparator> _winners;
	vector<WarriorPtr> _warriors;

	//unordered_map<WeaponPtr, WeaponViewPtr> _weaponViews;
	//unordered_map<WarriorPtr, WarriorViewPtr>_warriorViews;
	unordered_map<WarriorType, size_t> _warriorTypeAmounts;
};

class RedHeadquarters
: public Headquarters
{
public:
	RedHeadquarters(size_t elements)
	: Headquarters(RED, elements)
	{}

};

class BlueHeadquarters
: public Headquarters
{
public:
	BlueHeadquarters(size_t elements)
	: Headquarters(BLUE, elements)
	{}
};

/*********************HeadquartersView***************************/

class HeadquartersView
{
public:
	HeadquartersView(Headquarters * headquarters)
	: _headquarters(headquarters)
	{}

	void showLeftElements() const;
	void showBeTaken() const;
	//void showStopMessage() const;
	//void showWarriorAmount(WarriorType) const;
private:
	Headquarters * _headquarters;
};


}//end of namespace warcraft

#endif
