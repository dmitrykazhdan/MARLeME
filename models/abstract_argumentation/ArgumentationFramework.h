#ifndef ArgumentationFramework_H
#define ArgumentationFramework_H

#include "Argument.h"
#include <set>
#include <map>


using namespace std;

/*

Class representing an argumentation framework (AF), using argument identifiers.

allArguments - the set of arguments in the AF
attacks - attack relation
isAttackedBy - attack relation, using a different representation

*/

class ArgumentationFramework {
public:
    ArgumentationFramework();
    ArgumentationFramework (const ArgumentationFramework &oldAF); 
    ArgumentationFramework(set<int> &_allArguments);
    set<int> allArguments;
    map<int,set<int>> attacks;
    map<int,set<int>> isAttackedBy;
};

#endif