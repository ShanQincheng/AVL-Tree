# include "headFile.h"

bool JudgeIfPrime(int judgeNumber)
{
	int i = 0; // iterator variable
	if(judgeNumber == 2)  // 2 is a prime
		return true;
	else if(judgeNumber % 2 == 0) // can be divisible by 2 is not a prime
		return false;
	else{
		for(i = 2; i <= sqrt(judgeNumber); i++)
		{
			if(judgeNumber % i == 0)
				return false;
		}
		return true;
	}
}
