# include "headFile.h"

bool OutPutBinaryFile(vector<StuInfo> &stuInfoVector, string outPutFileName)
{
	int len = 0; // vector size
//	FILE *wFp;
	ofstream fout;
	fout.open(outPutFileName, ios::binary);
	
	if(!stuInfoVector.empty())
	{
		len = stuInfoVector.size();
	//	wFp = fopen(outPutFileName.c_str(), "w+");
		for(int i = 0; i < len; i++)
		{
		//	fwrite(&stuInfoVector[i], sizeof(StuInfo), 1, wFp);	
			fout.write((char *)(&stuInfoVector[i]), sizeof(StuInfo));
		}
//		fclose(wFp);
		
		cout << "~~ A binary file has been created! ~~" << endl;
		return true;
	}else{
		return false;
	}
	
}
