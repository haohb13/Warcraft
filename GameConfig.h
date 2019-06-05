 ///
 /// @file    GameConfig.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 20:51:16
 ///
 
#include "Types.h"
#include <map>
#include <vector>
#include <iostream>
using namespace std;
 
namespace warcraft
{

class GameConfig {
public:
	template <typename Iterator>
	void setWarriorOrder(Iterator beg, Iterator end)
	{
		while(beg != end) {
			_initWarriorOrder.push_back(*beg);
			++beg;
		}
	}

	void readFromConsole();
	void readFromFile(const string & filename);

	void nextGroupId() {	++_currentGroupId;	}

	size_t groups() const {	return _groups.size();	}
	size_t currentGroupId()	const {	return _currentGroupId;	}
	size_t cityCount() {	return _groups[_currentGroupId]._cityCount;	}
	size_t headquartersInitialElements();
	size_t warriorInitalLife(WarriorType key); 
	size_t warriorInitalAttack(WarriorType key);

	void debug() const;

	static GameConfig * getInstance()
	{
		if(nullptr == _pInstance) {
			_pInstance = new GameConfig();
		}
		return _pInstance;
	}

	static void destroy() 
	{
		if(_pInstance)
			delete _pInstance;
	}

private:
	GameConfig() : _currentGroupId(0){	cout << "GameConfig()" << endl;	}
	~GameConfig(){	cout << "~GameConfig()" << endl;	}
	void readFromStream(istream & is);

	struct InitData
	{
		size_t _initElements;
		size_t _cityCount;
		size_t _minutes;
		map<WarriorType, size_t> _initLifes;
		map<WarriorType, size_t> _initAttacks;
	};
private:
	static GameConfig * _pInstance;

	vector<InitData> _groups;
	size_t _currentGroupId;//当前组的测试数据的id
	vector<WarriorType> _initWarriorOrder;
};
 
}// end of namespace warcraft
