#ifndef VAFConstructor_H
#define VAFConstructor_H

#include <map>
#include "ArgumentationFramework.h"
#include "Ordering.h"


/*
This class computes a simplification of a given Argumentation Framework, using the
provided argument ordering, by removing all attacks where an argument of a lower value
attacks an argument of a higher value.
*/

class VAFConstructor {
public:
    static void constructVAF(ArgumentationFramework &af, Ordering &argOrdering, ArgumentationFramework &vaf);
};

#endif