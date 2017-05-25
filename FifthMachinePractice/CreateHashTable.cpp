# include "headFile.h"

void CreateHashTable(vector<StuInfo> stuInfoVector)
{
	int studentsNumber = stuInfoVector.size(); // input file total field number
	int hashSize = studentsNumber + 1; // size of the hashTable will be created
	int maxStepSize = studentsNumber / 3 + 1;
	int stepSize = -1; // double hashing step size
	int i = 0; // iterator variable
	int itemsNum; // the number of items 
	int nextStoreAddress = 0; // if collision, store to the next address
	double collisionNum = 0.0; // calculae the number of collisions
	double studentsNumberDouble = 0.0; // change studentsNumber from int to double , because the average compare time is double
	double sidAsciiSummation = 0.0;  // the ascii number each character of sid 	
	HashField *hashTable;   // dynamic array point
	HashField tempHashField; // Temporastore one student struction and a hvalue temporary
	
	do{
		if(JudgeIfPrime(hashSize)) // determine whether current hashsize is a prime number 
			break;
		else
			hashSize++;
	}while(true);  // calculate the hashSize
	do{
		if(JudgeIfPrime(maxStepSize))
			break;
		else
			maxStepSize++;
	}while(true); // calculate the maxStepSize
	
	hashTable = (HashField*)calloc(hashSize, sizeof(HashField)); // dynamic create a hashTable with hashSize
	
	for(i = 0; i < hashSize; i++)
	{
		hashTable[i].hvalue = -1;  // initial the hvalue of each item in the hashTable
	}
	
	for(i = 0; i < studentsNumber; i++)
	{
		sidAsciiSummation = CalculateSidAscii(stuInfoVector[i].sid);  // calculate the summation of the product of each ascii  
		//hashTable[i].hvalue = fmod(sidAsciiSummation, hashSize);
		tempHashField.stuInfoStruct = stuInfoVector[i];   // pick a student infomation to tempHashField
		tempHashField.hvalue = fmod(sidAsciiSummation, hashSize); // calculate the hvalue by the sid of the student

		collisionNum++;  // add collision time
		if(hashTable[tempHashField.hvalue].hvalue == -1)  // if current address is empty, just store
		{
			hashTable[tempHashField.hvalue].stuInfoStruct = tempHashField.stuInfoStruct;
			hashTable[tempHashField.hvalue].hvalue = tempHashField.hvalue;
		}else{ // if current address is full, find next address to store
			stepSize = maxStepSize - (fmod(sidAsciiSummation, maxStepSize)); // calculte the step size		
			nextStoreAddress = (tempHashField.hvalue + stepSize) % hashSize; // calculte next address of the hashTable to store

			while(true)
			{
				collisionNum++;  // add collision time

				if(hashTable[nextStoreAddress].hvalue == -1)  // if next address is empty, just store
				{
					hashTable[nextStoreAddress].stuInfoStruct = tempHashField.stuInfoStruct;
					hashTable[nextStoreAddress].hvalue = tempHashField.hvalue;
					
					break;
				}else{ // if next address is full, try to find next of the next address 
					nextStoreAddress = (nextStoreAddress + stepSize) % hashSize;

				}
			}
			
		}
		
	}
	printf("Hash Table Y is created.\n\n\n");

	for(i = 0; i < hashSize; i++)
	{
		if(hashTable[i].hvalue != -1)
			itemsNum++;
	}
	studentsNumberDouble = studentsNumber;
	printf("successful search : %.4lf comparisons on average\n\n\n", collisionNum / studentsNumberDouble);
	
	free(hashTable);
	
	return;
}
