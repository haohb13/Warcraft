 ///
 /// @file    Time.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-22 20:47:16
 ///
 
#include "GameTime.h"

namespace warcraft
{

pthread_once_t GameTime::_once = PTHREAD_ONCE_INIT;
GameTime * GameTime::_pInstance = getInstance();

GameTime * GameTime::getInstance()
{	
	pthread_once(&_once, init);
	return _pInstance;
}

void GameTime::init()
{	
	_pInstance = new GameTime();
	::atexit(destroy);
}

void GameTime::destroy()
{
	if(_pInstance)
		delete _pInstance;
}

void GameTime::updateTime()
{
	_minute += 10;
	if(_minute == 60) {
		_minute = 0;
		++_hour;
		_hour %= 24;
	}
}

void GameTime::showTime() const
{
	printf("%03lu:%02lu ", _hour, _minute);
}

}//end of namespace warcraft
