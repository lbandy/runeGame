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
			// collapse animation clearRunes �sszes elem�t elt�ntetj�k �s score-ozunk
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
			// collapse animation clearRunes �sszes elem�t elt�ntetj�k �s score-ozunk
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
			// collapse animation clearRunes �sszes elem�t elt�ntetj�k �s score-ozunk
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
amit ellen�rizn�nk kell:

norm�l helyeken:
pontosan f�l�tte l�v�t �s k�t mellette l�v�t
mellette l�v� kett�t
pontosan alatta l�v�t

els� mez�n�l: nem n�z�nk t�le balra (i % 9 == 0)
utols� mez�n�l nem n�z�nk t�le jobbra: (i % 9 == 8)

els� sor: nem n�z�nk felfel� (csak i+-1 �s i+9)
als� sor: nem n�z�nk lefel� (csak i+-1 �s i-9 +-1)

*/