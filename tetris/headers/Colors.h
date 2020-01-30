#pragma once
using namespace cv;
#include <ctime>

//----------- B ---G--- R
Scalar white(255, 255, 255);
Scalar gray(128, 128, 128);
Scalar black(1, 0, 0);
Scalar fullblack(0, 0, 0);

Scalar red(0, 0, 255);
Scalar green(0, 255, 0);
Scalar blue(255, 0, 0);
Scalar brown(0,75,150);

Scalar darkred(0, 0, 100);
Scalar darkgreen(0, 127, 0);
Scalar darkblue(127, 0, 0);
Scalar darkdarkblue(64, 0, 0);
Scalar darkdarkred(0, 0, 64);

Scalar yellow(0, 255, 255);
Scalar cyan(255, 255, 0);
Scalar magneta(255, 0, 255);

Scalar violet(255, 0, 128);

Scalar Tmagneta(255, 68, 255);
Scalar Tblue(255, 50, 50);
Scalar Tred(30, 30, 255);
Scalar Tyellow(30, 255, 255);
Scalar Tgreen(30, 255, 30);
Scalar Torange(0, 136, 255);
Scalar Tcyan(255, 255, 68);


Scalar tetrimino_color(int k)
{
	if (k > 6) { srand((unsigned int)time(NULL)); k = rand() % 7; }
	switch (k)
	{
	case 0: return Tmagneta;  break;
	case 1: return Tblue;  break;
	case 2: return Tred;  break;
	case 3: return Tyellow;  break;
	case 4: return Tgreen; break;
	case 5: return Torange; break;
	case 6: return Tcyan; break;
	}
};
