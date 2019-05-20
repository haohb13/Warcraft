 ///
 /// @file    Warrior.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-20 08:16:28
 ///
 
#include "Warrior.h"
#include <iostream>
using namespace std;
 
namespace warcraft
{

/**********************************/

string WarriorView::color(Color color) const
{
	return (color == RED) ? string("red"): string("blue");
}

void WarriorView::show() const
{
	cout <<	color(_warrior->getClor()) << " "
		 << _warrior->getName() << " "
		 << _warrior->getId() << " born with strength "
		 << _warrior->getHp() << endl;
}



/**********************************/
 
}// end of namespace warcraft
