#pragma once
#include "QueType.h"
#include <string>
using namespace std;
QueType<string> StringSplit(string strTarget, string strTok)
{
	int     nCutPos;
	int     nIndex = 0;
	QueType<string> Que;

	while ((nCutPos = strTarget.find_first_of(strTok)) != strTarget.npos) {
		if (nCutPos > 0)
			Que.Enqueue(strTarget.substr(0, nCutPos));
		strTarget = strTarget.substr(nCutPos + 1);
	}


	if (strTarget.length() > 0)
		Que.Enqueue(strTarget.substr(0, nCutPos));

	return Que;
}