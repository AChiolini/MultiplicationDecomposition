#ifndef SUBMULTIPLICATION_H
#define SUBMULTIPLICATION_H

class SubMultiplication
{
	private:
		short x;
		short y;
		short lengthX;
		short lengthY;

	public:
		SubMultiplication ();
		SubMultiplication (short, short, short, short);
		short getX();
		short getY();
		short getLengthX();
		short getLengthY();
		void setX(short);
		void setY(short);
		void setLengthX(short);
		void setLengthY(short);
		virtual ~SubMultiplication () = default;
};

#endif
