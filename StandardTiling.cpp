#include <iostream>
#include <vector>
#include <math.h>
#include "StandardTiling.h"

using namespace std;

StandardTiling::StandardTiling(Multiplier *multipliers, int nMultipliers)
{
    this->multipliers = multipliers;
    this->nMultipliers = nMultipliers;
}

Configuration* StandardTiling::dispositions(short lengthX, short lengthY, int *nDispositions)
{
    vector <Configuration> configurations;
    int i;

    for (i=0; i<nMultipliers;i++)
    {
        configurations.push_back(dispose(lengthX, lengthY, i));
    }
    if (configurations.size() > 0)
    {
        *nDispositions = configurations.size();
        return &configurations[0];
    }
    else 
    {
        *nDispositions = 0;
        return NULL;
    }
}

Configuration StandardTiling::dispose(short x, short y, int index)
{
    short dim1; 
    short dim2;
    short max;
    short min;
    int levels, delay;
    int nmaxv, nminv, countv, nmaxh, nminh, counth, i, j, k, n, nmaxtmp, lX, lY;
    bool match;
    vector <SubMultiplication> subMultiplications;
    Configuration *tmp;
	
    dim1 = multipliers[index].getInputLenght1() - 1;
    dim2 = multipliers[index].getInputLenght2() - 1;
    match = false;
    if (dim1 > dim2)
    {
	max = dim1;
	min = dim2;
    }
    else
    {
	max = dim2;
	min = dim1;
    }	
    if (max == min)
    {
	//se il moltiplicatore è un quadrato mappo tutto fino a che non copro tutta la moltiplicazione
	for (i = 0; i * max < x; i++)
	{
	    if ((i + 1) * max > x)
		lX = max - ((i + 1) * max) + x;
	    else
		lX = max;
	    for (j = 0; j * max < y; j++)
	    {
		if ((j + 1) * max > y)
		    lY = max - ((j + 1) * max) + y;
		else
		    lY = max;
		subMultiplications.push_back (SubMultiplication (((short) (i * max)), ((short) (j * max)), (short) lX, (short) lY, multipliers[index]));
	    }
	}
    }
    else
    {
	if (x != y)
    	{
	    //se la moltiplicazione ha due ingressi di lunghezza diversa controllo prima se posso matchare la verticale
	    for (countv = 0, nmaxv = 0; countv < y; countv = countv + max, nmaxv++);
	    do
	    {
	        nmaxv--;
	        for (countv = nmaxv * max, nminv = 0; countv < y;  countv = countv + min, nminv++);
	        if (countv == y)
		    match = true;
	    } while (match == false && nmaxv > 0);
	}
	if (match == false)
	{
	    //se non posso mappo l'orizzontale
	    for (counth = 0, nmaxh = 0; counth < x; counth = counth + max, nmaxh++);
	    nmaxtmp = nmaxh;
	    do
	    {
		nmaxh--;
		for (counth = nmaxh * max, nminh = 0; counth < x;  counth = counth + min, nminh++);
		if (counth == x)
		    match = true;
	    } while (match == false && nmaxh > 0);
	    if (match == false)
	    {
		nmaxh = nmaxtmp;
	     	nminh = 0;
	    }
	    for (i = 0; i < nmaxh; i++)
	    {
		if ((i + 1) * max > x)
		    lX = max - ((i + 1) * max) + x;
	        else
		    lX = max;
		for (j = 0; j * min < y; j++)
		{
		    if ((j + 1) * min > y)
		        lY = min - ((j + 1) * min) + y;
		    else
			lY = min;
		    subMultiplications.push_back (SubMultiplication (((short) (i * max)), ((short) (j * min)), (short) lX, (short) lY, multipliers[index]));
		}
	    }
	    for (k = 0; k < nminh; k++)
	    {
		if ((i * max) + ((k + 1) * min) > x)
		    lX = min - ((i * max) + ((k + 1) * min)) + x;
	        else
		    lX = min;
		for (j = 0; j * max < y; j++)
		{
		    if ((j + 1) * max > y)
		        lY = max - ((j + 1) * max) + y;
		    else
			lY = max;
		    subMultiplications.push_back (SubMultiplication (((short) ((i * max) + (k * min))), ((short) (j * max)), (short) lX, (short) lY, multipliers[index]));	    
		} 
	    }
	}
	else
	{
	    //match verticale
	    for (i = 0; i < nmaxv; i++)
	    {
		if ((i + 1) * max > y)
		    lY = max - ((i + 1) * max) + y;
	        else
		    lY = max;
		for (j = 0; j * min < x; j++)
		{
		    if ((j + 1) * min > x)
		        lX = min - ((j + 1) * min) + x;
		    else
			lX = min;
		    subMultiplications.push_back (SubMultiplication (((short) (j * min)), ((short) (i * max)), (short) lX, (short) lY, multipliers[index]));
		}
	    }
	    for (k = 0; k < nminv; k++)
	    {
		if ((i * max) + ((k + 1) * min) > y)
		    lY = min - ((i * max) + ((k + 1) * min)) + y;
	        else
		    lY = min;
		for (j = 0; j * max < x; j++)
		{
		    if ((j + 1) * max > x)
		        lX = max - ((j + 1) * max) + x;
		    else
			lX = max;
		    subMultiplications.push_back (SubMultiplication (((short) (j * max)), ((short) ((i * max) + (k * min))), (short) lX, (short) lY, multipliers[index]));
		}		    
	    }
	}
    }
    if (subMultiplications.size() > 0)
    {
	for (levels = 0; pow (2.0, levels) < subMultiplications.size(); levels++);
	delay = levels + multipliers[index].getDelay();
    }
    else
	delay = 0;
    tmp = new Configuration(&subMultiplications[0], subMultiplications.size(), delay);
    //dovrei avere l´array pronto in questo punto
    for (i = 0; i < subMultiplications.size(); i++)
    {
	cout << "(" << subMultiplications[i].getX() << ", " << subMultiplications[i].getY() << ", ";
	cout << subMultiplications[i].getLengthX() << ", " << subMultiplications[i].getLengthY() << ")" << endl;
    }
    cout << "Delay: " << delay << endl;
    return Configuration(&subMultiplications[0], subMultiplications.size(), delay);
}