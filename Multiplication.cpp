#include <fstream>
#include <iostream>
#include <vector>
#include "Multiplication.h"

using namespace std;

Multiplication::Multiplication ()
{
    int i;
    short input1, input2, minInput1, minInput2;
    ifstream infile("multipliers");
    Multiplier *tmp;
    Multiplier *tmpArray;

    nMultipliers = 0;
    while (infile >> input1 >> input2 >> minInput1 >> minInput2)
    {	
	try
	{
	    tmp = new Multiplier (input1, input2, minInput1, minInput2);		
	    if (nMultipliers == 0)
	    {
		multipliers = new Multiplier[1];
		multipliers[0] = Multiplier (tmp->getInputLenght1(), tmp->getInputLenght2(), tmp->getMinInput1(), tmp->getMinInput2());
	    }
	    else
	    {
		tmpArray = new Multiplier[nMultipliers + 1];
		for (i = 0; i < nMultipliers; i++)
		    tmpArray[i] = Multiplier(multipliers[i].getInputLenght1(), multipliers[i].getInputLenght2(), multipliers[i].getMinInput1(), multipliers[i].getMinInput2());
		tmpArray[nMultipliers] = Multiplier (tmp->getInputLenght1(), tmp->getInputLenght2(), tmp->getMinInput1(), tmp->getMinInput2());
		delete[] multipliers;
		multipliers = tmpArray;
	    }
	    nMultipliers++;
	}
	catch (const invalid_argument& e)
	{
	    cerr << e.what() << endl;
	}
    }
}

void Multiplication::printMultipliers ()
{
    int i;
	
    cout << "Number of multipliers " << nMultipliers << endl;
    for(i=0; i < nMultipliers; i++)
    {
	cout << i+1 << ") " << multipliers[i].getInputLenght1() << " x " << multipliers[i].getInputLenght2() << " ( " << multipliers[i].getMinInput1() << " x " << multipliers[i].getMinInput2() << " ) " << endl;
    }
}

long long Multiplication::multiply (short inputLenght1, long long value1, short inputLenght2, long long value2)
{
	int i;
	for (i=0; i<nMultipliers; i++){
	 cout << i+1 << ") " << multipliers[i].getInputLenght1() << " x " << multipliers[i].getInputLenght2() << " ( " << multipliers[i].getMinInput1() << " x " << multipliers[i].getMinInput2() << " ) " << endl;
     standardDisposition (multipliers[i], inputLenght1, inputLenght2);
	 cout << endl;
	}
}

SubMultiplication* Multiplication::standardDisposition (Multiplier mult, short x, short y)
{
    short dim1; 
    short dim2;
    short max;
    short min; 
    int nmaxv, nminv, countv, nmaxh, nminh, counth, i, j, k, n, nmaxtmp;
    bool match;
    vector <SubMultiplication> subMultiplications;
    SubMultiplication *tmp;
	
    dim1 = mult.getInputLenght1() - 1;
    dim2 = mult.getInputLenght2() - 1;
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
	    for (j = 0; j * max < y; j++)
		subMultiplications.push_back (SubMultiplication (((short) (i * max)), ((short) (j * max)), max, max));
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
		for (j = 0; j * min < y; j++)
		    subMultiplications.push_back (SubMultiplication (((short) (i * max)), ((short) (j * min)), max, min));
	    }
	    for (k = 0; k < nminh; k++)
	    {
		for (j = 0; j * max < y; j++)
		    subMultiplications.push_back (SubMultiplication (((short) ((i * max) + (k * min))), ((short) (j * max)), min, max));
	    } 
	}
	else
	{
	    //match verticale
	    for (i = 0; i < nmaxv; i++)
	    {
		for (j = 0; j * min < x; j++)
		    subMultiplications.push_back (SubMultiplication (((short) (j * min)), ((short) (i * max)), min, max));
	    }
	    for (k = 0; k < nminv; k++)
	    {
		for (j = 0; j * max < x; j++)
		    subMultiplications.push_back (SubMultiplication (((short) (j * max)), ((short) ((i * max) + (k * min))), max, min));
	    }
	}
    }
    //dovrei avere l´array pronto in questo punto
    for (i = 0; i < subMultiplications.size(); i++)
    {
	cout << "(" << subMultiplications[i].getX() << ", " << subMultiplications[i].getY() << ", ";
	cout << subMultiplications[i].getLengthX() << ", " << subMultiplications[i].getLengthY() << ")" << endl;
    }
    return NULL;
}
