#include "VAFConstructor.h"

void VAFConstructor::constructVAF(ArgumentationFramework &af,
                Ordering &argOrdering,
                ArgumentationFramework &vaf) {

    for (auto argument : af.allArguments) {
        vaf.allArguments.insert(argument);
        set<int> emptySet1;
        set<int> emptySet2;
        vaf.attacks.insert({argument, emptySet1});
        vaf.isAttackedBy.insert({argument, emptySet2});
    }

    int v1;
    int v2;

    for (auto arg1 : vaf.allArguments) {
        for (auto arg2 : vaf.allArguments) {

            if (af.attacks[arg1].find(arg2) != af.attacks[arg1].end()) {

                v1 = argOrdering.getValue(arg1);
                v2 = argOrdering.getValue(arg2);

                if (v1 >= v2) {
                    vaf.attacks[arg1].insert(arg2);
                    vaf.isAttackedBy[arg2].insert(arg1);
                }
            }
        }
    }
}
