# include "headFile.h"

vector<StuInfo>& ReadBinaryFile(vector<StuInfo> &stuInfoVector, string outPutFileName)
{
	int len = 12; // vector size
	StuInfo stuInfoStruct;
 	ifstream inF;  
  	inF.open(outPutFileName, std::ifstream::binary);  // use binary mode to read a binary file
  	
	if(inF == NULL)
	{
		stuInfoVector.clear();
		return stuInfoVector;
	}else{
		while(!(inF.peek() == EOF))
		{
			inF.read(reinterpret_cast<char*>(&stuInfoStruct), sizeof(stuInfoStruct)*1);  // read one student information
			stuInfoVector.push_back(stuInfoStruct);	
		}
		inF.close();  
		return stuInfoVector;
	}
}
