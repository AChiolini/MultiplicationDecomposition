#include "Int128Operations.h"

using namespace std;

__int128 Int128Operations::getInt128(const char *p)
{
    int32_t digit, isneg;
    __int128 value;

    isneg = 0;
    value = 0;
    for (; isspace (*p); p++);	/* gobble up leading whitespace */
    /* do I have a sign? */
    if (*p == '-') 
    {
        isneg = 1;
        p++;
    }
    else if (*p == '+')
    {
	p++;
    }
    for (; *p; p++) 
    {
        if (*p >= '0' && *p <= '9')
        {
            digit = *p - '0';
        }
	else
        {
            break;
        }	
        value *= 10;
        value += digit;
    }
    if (isneg)
    {
        value = 0 - value;
    }
    return (value);
}

string Int128Operations::getString(__int128 n)
{
    string s;
    __int128 copy;

    copy = n;
    s = "";
    if (n != 0)
    {
        while (n != 0)
        {
            s = (char) ((n % 10) + 48) + s;
            n = n / 10;
        }
        if (copy < 0)
        {
            s = "-" + s;
        }
    }
    else
    {
        s = "0";
    }
    return s;
}
