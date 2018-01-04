#ifndef INT128OPERATIONS_H
#define INT128OPERATIONS_H

#include <string>

using namespace std;

/*****************************************************************************/
/* Class that helps the usage of __int128 variables.                         */
/*****************************************************************************/

class Int128Operations
{
    public:
        static __int128 getInt128(const char*);
        static string getString(__int128 n);
};

#endif
