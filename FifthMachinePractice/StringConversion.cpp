#include "headFile.h"

unsigned char StringConversion::stringToUnsignedChar(string str)
{
	unsigned char result;
	unsigned short intResult;
	istringstream iss(str);
		
	iss >> intResult;
//	cout << intResult << 't';
	result = (unsigned char)intResult;
		
	return result;	
}	


float StringConversion::stringToFloat(string str)
{
	float result;
	istringstream iss(str);
	
	iss >> result;
	
	return result;
}

