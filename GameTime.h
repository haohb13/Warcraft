 ///
 /// @file    GameTime.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-22 20:38:33
 ///
 
#ifndef __WARCRAFT_GAMETIME_H__
#define __WARCRAFT_GAMETIME_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

namespace warcraft
{

class GameTime
{
public:
	static GameTime * getInstance();

	static void init();

	static void destroy();

	size_t getTime() const {	return _hour;	}
	void showTime() const;
	void updateTime();
	void reset()
	{	_hour = 0; _minute = 0;	}
private:
	GameTime(size_t hour = 0, size_t minute = 0)
	: _hour(hour)
	, _minute(minute)
	{}	

private:
	static GameTime * _pInstance;
	static pthread_once_t _once;
	size_t _hour;
	size_t _minute;
};

}//end of namespace warcraft

#endif
