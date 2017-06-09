#ifndef MULTIPLIER_H
#define MULTIPLIER_H

class Multiplier
{
	private:
		short inputLength1;
		short inputLength2;
		short minInput1;
		short minInput2;

	public:
		Multiplier ();
		Multiplier (short inputLength1, short inputLength2, short minInput1, short minInput2);
		short getInputLenght1 ();
		short getInputLenght2 ();
		short getMinInput1();
		short getMinInput2();
		void setInputLenght1 (short inputLength);
		void setInputLenght2 (short inputLength);
		void setMinInput1 (short minInput1);
		void setMinInput2 (short minInput2);
		virtual ~Multiplier () = default;
};

#endif
