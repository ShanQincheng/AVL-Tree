# include "headFile.h"

/*
	calculate each character ascii number product summation of the sid 
*/
double CalculateSidAscii(char* sid) 
{
	char *p = sid;
	double totalResult = (*p - '0') + 48;

	p++;
	while(*p != '\0')
	{
		totalResult *= (*p - '0') + 48;
		p++;
	} 
	
	return totalResult;
}
