#include <map>
#include "GESolver.h"
#include "Argument.h"

using namespace std;

void GESolver::solve(ArgumentationFramework af, set<set<int>> &extension) {
    
    set<int> unmarkedArgs;
    set<int> deletedArgs;
    set<int> groundedExtension;

    // Set all arguments as unmarked
    for(auto arg : af.allArguments) {
        unmarkedArgs.insert(arg);
    }

    bool changed = true;

    while (changed) {
        
        changed = false;
        deletedArgs.clear();
        
        for(auto itr = unmarkedArgs.begin(); itr != unmarkedArgs.end();) {
            if (af.isAttackedBy[*itr].size() == 0) {
                
                groundedExtension.insert(*itr);
               
                for (auto arg : af.attacks[*itr]) {
                    deletedArgs.insert(arg);
                }       
                itr = unmarkedArgs.erase(itr);
                changed = true;
            } else {
                ++itr;
            }
        }
        
        if (deletedArgs.size() > 0) {
            for (auto deletedArg : deletedArgs) {
                unmarkedArgs.erase(deletedArg);            
            }

            for (auto it = af.isAttackedBy.begin(); it != af.isAttackedBy.end(); it++) {
                for (auto deletedArg : deletedArgs) {
                    it->second.erase(deletedArg);                    
                }
            }  
        }
    }  
    extension.insert(groundedExtension);
}