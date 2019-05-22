 ///
 /// @file    Mylogger.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-20 09:42:26
 ///
 

#ifndef __WD_MYLOGGER_H__
#define __WD_MYLOGGER_H__

#include <log4cpp/Category.hh>

#include <stdlib.h>
#include <string>
using std::string;

using namespace log4cpp;

#define prefix(msg) string(" [").append(__FILE__)\
		.append(":").append(__FUNCTION__)\
		.append(":").append(std::to_string(__LINE__)).append("] ")\
		.append(msg)

namespace wd
{

class Mylogger
{
public:
	enum PRIORITY{
		ERROR = 0,
		WARN,
		INFO,
		DEBUG
	};

	void setPriority(PRIORITY p);

	static Mylogger * getInstance() 
	{	
		if(_pInstance == nullptr) {
			_pInstance = new Mylogger();
			//::atexit(destroy);
		}
		return _pInstance;
	}

	static void destroy() 
	{
		if(_pInstance)
			delete _pInstance;
	}

	void error(const char * msg);

	template <typename... Args>
	void error(Args... args)
	{	_mylogger.error(args...);	}

	void warn(const char * msg);

	template <typename... Args>
	void warn(Args... args)
	{	_mylogger.warn(args...);	}

	void info(const char * msg);

	template <typename... Args>
	void info(Args... args)
	{	_mylogger.info(args...);	}

	void debug(const char * msg);

	template <typename... Args>
	void debug(Args... args)
	{	_mylogger.error(args...);	}
private:
	Mylogger();
	~Mylogger();

private:
	static Mylogger * _pInstance;
	Category & _mylogger;
};


}//end of namespace wd

#define LogError(msg, ...) wd::Mylogger::getInstance()->error(prefix(msg).c_str(), ##__VA_ARGS__)
#define LogInfo(msg, ...) wd::Mylogger::getInstance()->info(prefix(msg).c_str(), ##__VA_ARGS__)
#define LogWarn(msg, ...) wd::Mylogger::getInstance()->warn(prefix(msg).c_str(), ##__VA_ARGS__)
#define LogDebug(msg, ...) wd::Mylogger::getInstance()->debug(prefix(msg).c_str(), ##__VA_ARGS__)

#endif
