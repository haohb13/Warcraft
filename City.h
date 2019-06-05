 ///
 /// @file    City.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-28 21:15:53
 ///
 
#pragma once

#include "Types.h"
#include <vector>
using std::vector;

namespace warcraft
{

class City
{
public:
	City(size_t id, size_t elements = 0)
	: _flag(Color::NOTSET)
	, _id(id)
	, _elements(elements)
	, _redWinCount(0)
	, _blueWinCount(0)
	{}

	size_t getWarriorAmount() const {	return _redWarriors.size() + _blueWarriors.size();	}
	vector<WarriorPtr> & getRedWarriors() {	return _redWarriors;	}
	vector<WarriorPtr> & getBlueWarriors() {	return _blueWarriors;	}

	WarriorPtr getSoloWarrior() 
	{	
		if(_redWarriors.size() == 0) 
			return *_blueWarriors.begin();	
		else 
			return *_redWarriors.begin();
	}

	void takenBy(WarriorPtr warrior);
	void produceElements();
	void attach(WarriorPtr);
	void detach(WarriorPtr);
	void startBattle();
	size_t getId() const {	return _id;	}
	Color getFlag() const {	return _flag;	}
private:
	void battle(WarriorPtr warrior1, WarriorPtr warrior2);
	bool isChangingFlag(WarriorPtr warrior);

private:
	Color _flag;//旗子颜色
	size_t _id;
	size_t _elements;//生命元数量
	size_t _redWinCount;
	size_t _blueWinCount;
	vector<WarriorPtr> _redWarriors;
	vector<WarriorPtr> _blueWarriors;
	//vector<WarriorPtr> _warriors;
};

class CityView
{
public:
	CityView(City * city) : _city(city) {}

	void showFlag() const;
private:
	City * _city;
};

}//end of namespace warcraft
