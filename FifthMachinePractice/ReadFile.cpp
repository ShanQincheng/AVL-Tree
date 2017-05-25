# include "headFile.h"

	/*
		Read the student information file, split each single student information 
		and then store each single student into a stuInfo Structre.
		push_back each stu info structure the into stuInfoVector
	*/
vector<StuInfo>& ReadFile(string fileName, vector<StuInfo> &stuInfoVector) 
{
	ifstream inFile;
	string data; // one line student information, store in a string
	char delim = '\t'; // use '\t' symbol to split one line student information
	vector<string> singleElement; // store each information element for one student, just for one student
	StringConversion stringConversion; // string conversion class, having functions such as string -> unsigned char, string -> float etc.
		
	inFile.open(fileName, ios::in); // link the file stream with the file
//	assert(inFile.is_open());  // if it fails, output an error message and terminate the program to run
	if(inFile.fail())
	{
		stuInfoVector.clear();
		
		return stuInfoVector;
	}
	
	int k = 0;
	StuInfo *stuInfoStruct;
	StuInfo *p;
	
	p = stuInfoStruct;
	
	while(getline(inFile, data))  // read one line content in .txt file
	{	
		SplitString(data, delim, singleElement, true);  // split the line into single string by '\t'
		int len = singleElement.size();  // check how many single strings in one line
		
		p = (StuInfo *)calloc(1, sizeof(StuInfo)); // calloc a student information struct to store one line student information
		for(int i = 0; i < len; i++)  // iterate information string for one student
		{		
			if(i == 0)  // deal with student school number
			{
				strcpy(p->sid, singleElement[i].c_str()); // store sid into stuinfo structure
			}else if(i == 1){ // deal with student school id
				strcpy(p->sname, singleElement[i].c_str()); // store sname into stuinfo structure
			}else if(i >= 2 && i <= 13){ // deal with student score
				p->score[i-2] = stringConversion.stringToUnsignedChar(singleElement[i]); // store 12 scores into stuinfo structure
			}else if(i == 14){ // deal with the last information, average score		
				p->average = stringConversion.stringToFloat(singleElement[i]); // store average score into stuinfo structure
			}else{
				exit(1);
			}
		}
		stuInfoVector.push_back(*p);  // store one line information (one student information) in a vector		p++;  // pointer forward
		singleElement.clear(); // clean the temp student structure for next iterator to store another student information
	}
	inFile.close(); // close the student information file which was opened
	
	/*
	    return the vector that contains all the student information 
		in the student file which was opened, 
		one student information is stored by a stuinfo structure 
	*/
	return stuInfoVector; 
}


