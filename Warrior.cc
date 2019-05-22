 ///
 /// @file    Warrior.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-20 08:16:28
 ///
 
#include "Warrior.h"

#include "Mylogger.h"
#include <iostream>
using namespace std;
 
namespace warcraft
{

/**********************************/


void WarriorView::show() const
{
	cout <<	toString(_warrior->getClor()) << " "
		 << _warrior->getName() << " "
		 << _warrior->getId() << " born with strength "
		 << _warrior->getHp() << ",";
}

/**********************************/
 
}// end of namespace warcraft
