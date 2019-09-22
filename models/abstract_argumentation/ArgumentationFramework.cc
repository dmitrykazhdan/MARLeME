#include "ArgumentationFramework.h"


ArgumentationFramework::ArgumentationFramework() :
allArguments(), attacks(), isAttackedBy() {

}

ArgumentationFramework::ArgumentationFramework(const ArgumentationFramework &oldAF) : 
    allArguments(oldAF.allArguments),
    attacks(oldAF.attacks), 
    isAttackedBy(oldAF.isAttackedBy) {

} 


ArgumentationFramework::ArgumentationFramework(set<int> &_allArguments) :
allArguments(_allArguments), attacks(), isAttackedBy() {
}

