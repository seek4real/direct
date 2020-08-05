#pragma once

/*
** locstring.h
** local string class for display or print.
*/

class localstring
{
public:
	localstring();
	~localstring();

	localstring(char*);
private:
	char* str;
};

