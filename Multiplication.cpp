#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include "Multiplication.h"


using namespace std;

Multiplication::Multiplication()
{
    int i, delay;
    short input1, input2, minInput1, minInput2;
    vector <Multiplier> array;
    ifstream infile("multipliers");

    nMultipliers = 0;
    while (infile >> input1 >> input2 >> minInput1 >> minInput2 >> delay)
    {	
	try
	{
	    array.push_back(Multiplier (input1, input2, minInput1, minInput2, delay));		
	}
	catch (const invalid_argument& e)
	{
	    cerr << e.what() << endl;
	}
    }
    nMultipliers = array.size();
    if (nMultipliers > 0)
    	multipliers = &array[0];
}

void Multiplication::printMultipliers()
{
    int i;
	
    cout << "Number of multipliers " << nMultipliers << endl;
    for(i=0; i < nMultipliers; i++)
    {
	cout << i+1 << ") " << multipliers[i].getInputLenght1() << "x" << multipliers[i].getInputLenght2() << " (" << multipliers[i].getMinInput1() << "x" << multipliers[i].getMinInput2() << ")" << endl;
    }
}

long long Multiplication::multiply(short inputLenght1, long long value1, short inputLenght2, long long value2)
{
    int i;
    for (i=0; i<nMultipliers; i++)
    {
	cout << i+1 << ") " << multipliers[i].getInputLenght1() << "x" << multipliers[i].getInputLenght2() << " (" << multipliers[i].getMinInput1() << "x" << multipliers[i].getMinInput2() << ")" << endl;
     standardDisposition (&multipliers[i], (long long) inputLenght1 - 1, (long long) inputLenght2 - 1);
	cout << endl;
    }
}

Configuration* Multiplication::standardDisposition(Multiplier *mult, short x, short y)
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
	
    dim1 = mult->getInputLenght1() - 1;
    dim2 = mult->getInputLenght2() - 1;
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
		subMultiplications.push_back (SubMultiplication (((short) (i * max)), ((short) (j * max)), (short) lX, (short) lY, mult));
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
		    subMultiplications.push_back (SubMultiplication (((short) (i * max)), ((short) (j * min)), (short) lX, (short) lY, mult));
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
		    subMultiplications.push_back (SubMultiplication (((short) ((i * max) + (k * min))), ((short) (j * max)), (short) lX, (short) lY, mult));	    
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
		    subMultiplications.push_back (SubMultiplication (((short) (j * min)), ((short) (i * max)), (short) lX, (short) lY, mult));
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
		    subMultiplications.push_back (SubMultiplication (((short) (j * max)), ((short) ((i * max) + (k * min))), (short) lX, (short) lY, mult));
		}		    
	    }
	}
    }
    if (subMultiplications.size() > 0)
    {
	for (levels = 0; pow (2.0, levels) < subMultiplications.size(); levels++);
	delay = levels + mult->getDelay();
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
    return tmp;
}
