 ///
 /// @file    TestWarcraft.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-19 20:46:47
 ///
 
#include "Mylogger.h"
#include "GameConfig.h"
#include "WarcraftWorld.h"

#include <vector>
#include <iostream>
using namespace std;
using namespace warcraft;
 
int test0()
{
	//武士生命值设置时的顺序
	vector<WarriorType> types1 = {
		DRAGON_TYPE, 
		NINJA_TYPE, 
		ICEMAN_TYPE, 
		LION_TYPE, 
		WOLF_TYPE
	};
	//Red: 武士制造的顺序
	vector<WarriorType> types2 = {
		ICEMAN_TYPE, 
		LION_TYPE, 
		WOLF_TYPE,
		NINJA_TYPE, 
		DRAGON_TYPE, 
	};
	//Blue:武士制造的顺序
	vector<WarriorType> types3 = {
		LION_TYPE, 
		DRAGON_TYPE, 
		NINJA_TYPE, 
		ICEMAN_TYPE, 
		WOLF_TYPE
	};

	GameConfig::getInstance()->setWarriorOrder(types1.begin(), types1.end());
	GameConfig::getInstance()->readFromFile("warcraft.conf");
	//GameConfig::getInstance()->readFromFile(argv[1]);
	//GameConfig::getInstance()->readFromConsole();
	GameConfig::getInstance()->debug();

#if 1
	size_t groups = GameConfig::getInstance()->groups();
	for(size_t groupId = 0; groupId != groups; ++groupId) {
		printf("Case:%lu\n", groupId + 1);
		WarcraftWorld wow;
		wow.setRedWarriorCreatingOrder(types2.begin(), types2.end());
		wow.setBlueWarriorCreatingOrder(types3.begin(), types3.end());
		wow.start();
		
		GameConfig::getInstance()->nextGroupId();
	}
#endif
	
	GameConfig::destroy();
	wd::Mylogger::destroy();

	return 0;
}


int main(int argc, char ** argv)
{
	test0();
	return 0;
}
