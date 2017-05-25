# include "headFile.h"

/*
	str : one student information, read one line and stored by a string
	delim: the symbol to be splited
	elems: store each information for the student, i.e. sid, sname etc.
*/
vector<string> &SplitString(const string &str, char delim, vector<string> &elems, bool skip_empty = true)
{
	istringstream iss(str); // deal with the string
	
	for(string item; getline(iss, item, delim);) // iterator the student's each information which splited by '\t' symbol
	{
		if(skip_empty && item.empty()) // skip the empty information
		{
			elems.push_back(NULL);
			continue;
		}else{
			elems.push_back(item);
		}
	}
	
	return elems;
}
