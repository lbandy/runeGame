#include "stdafx.h"

bool RuneOperations::CheckMatches(int* runes[], std::vector<int> &clearRunes)
{
	bool result = false;

	for (int i = 0; i < 45; i++)
	{
		int matches = 0;
		if (*runes[i] == *runes[i + 1])
		{
			matches++;
			if (*runes[i + 1] == *runes[i + 2]) // tole jobbra lefele levo
			{
				matches++;
				clearRunes.push_back(i);
			}
		}

		if (*runes[i] == *runes[(i - 9) - 1]) // tole balra felfele levo
		{
			matches++;
			if (*runes[(i - 9) - 1] == *runes[(i - 9) - 2])
			{
				matches++;
				clearRunes.push_back(i);
			}
		}

		if (matches >= 3)
		{
			// collapse animation clearRunes összes elemét eltüntetjük és score-ozunk
			clearRunes.clear();
			result = true;
		}


		matches = 0;
		if (*runes[i] == *runes[i - 1])
		{
			matches++;
			if (*runes[i - 1] == *runes[i - 2]) // tole balra lefele levo
			{
				matches++;
				clearRunes.push_back(i);
			}
		}

		if (*runes[i] == *runes[(i - 9) + 1]) // tole jobbra felfele levo
		{
			matches++;
			if (*runes[(i - 9) + 1] == *runes[(i - 9) + 2])
			{
				matches++;
				clearRunes.push_back(i);
			}
		}

		if (matches >= 3)
		{
			// collapse animation clearRunes összes elemét eltüntetjük és score-ozunk
			clearRunes.clear();
			result = true;
		}

		matches = 0;
		if (*runes[i] == *runes[i + 1])
		{
			matches++;
			if (*runes[i + 1] == *runes[i + 2]) // tole jobbra lefele levo
			{
				matches++;
				clearRunes.push_back(i);
			}
		}

		if (*runes[i] == *runes[(i - 9) - 1]) // tole balra felfele levo
		{
			matches++;
			if (*runes[(i - 9) - 1] == *runes[(i - 9) - 2])
			{
				matches++;
				clearRunes.push_back(i);
			}
		}

		if (matches >= 3)
		{
			// collapse animation clearRunes összes elemét eltüntetjük és score-ozunk
			clearRunes.clear();
			result = true;
		}

	}

	return result;
}

void MoveRune(int* runes[], int sourceIndex, int targetIndex)
{

}

/*
amit ellenõriznünk kell:

normál helyeken:
pontosan fölötte lévõt és két mellette lévõt
mellette lévõ kettõt
pontosan alatta lévõt

elsõ mezõnél: nem nézünk tõle balra (i % 9 == 0)
utolsó mezõnél nem nézünk tõle jobbra: (i % 9 == 8)

elsõ sor: nem nézünk felfelé (csak i+-1 és i+9)
alsó sor: nem nézünk lefelé (csak i+-1 és i-9 +-1)

*/