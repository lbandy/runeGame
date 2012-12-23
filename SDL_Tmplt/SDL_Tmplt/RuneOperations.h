#ifndef RUNEOPERATIONS_H
#define RUNEOPERATIONS_H

class RuneOperations
{
public:
	bool CheckMatches(int* runes[], std::vector<int> &clearRunes);

	void MoveRune(int* runes[], int sourceIndex, int targetIndex);
	
};

#endif