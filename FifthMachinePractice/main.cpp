// T07
// 10427136 蔡易珊
// 04106034 何政霖


#include <iostream>	 // cout, endl
#include <fstream>   // open, is_open
#include <string>
#include <string.h>  // string
#include <assert.h>
#include <sstream>
#include <vector>    // vector
#include <math.h>
#include <cstdlib>   // atoi, system
#include <iomanip>   // setw
#include <new>       // new, delete
#include <ctime> // clock, CLOCKS_PER_SEC
using namespace std;					   // standard naming space

typedef struct Class {
  char studentID[16] ;
  char studentName[16] ;
  unsigned char score[12] ;
  float average = 0.0 ;
} Data ;

typedef struct Hashtable {
  int Hashvalue = -1 ;
  char sID[16] ;
  char sName[16] ;
  float Aver = 0.0 ;
  int collision = 0 ;
} Hash ;

typedef struct stuInfo
{
	char sid[16] = {};
	char sname[16] = {};
	unsigned char score[12] = {};
	float average = 0.0;	
}StuInfo;

typedef struct hashField
{	
	StuInfo stuInfoStruct;
	int hvalue = -1;
}HashField;


bool getBinRecords( vector<Data> &Alldata, string fileName ) {                              // get records from a binary file as a result
	// in: number of students, file name; out: a set of records
  fstream  inFile;      // input file handle
  Data     onestudent;    // keep one record with all the required fields
  int      studentnum = 0 ;

  fileName = "input" + fileName + ".dat" ;
  inFile.open( fileName.c_str(), fstream::in | fstream::binary );			// open a binary file
  if (!inFile.is_open()) {
    cout << endl << fileName << " does not exist!!!" << endl;
    return false;
  } // if
  inFile.seekg (0, inFile.end); // seekg()是設置讀位置(偏移量 offset 所能取得的最大值,移動的基準位置)
  studentnum = inFile.tellg() / sizeof(Data);			   // compute the total number of student records
  // tellg() 返回一個int型數值，它表示“內置指標”的目前位置。
  inFile.seekg (0, inFile.beg);
  for (int i = 0 ; i < studentnum ; i++) {
    inFile.read((char *)&onestudent, sizeof(onestudent));  // read the entire record from a binary file
    Alldata.push_back(onestudent);                         // add a record into the collection
  }   //end for
  inFile.close();                                    // close input file
  if (Alldata.size())
    return true;								// it succeeds if there is at least one records

  return false;
}   // end getBinRecords

bool isPrime( int prime ) {
  for( int i = 2 ; i < prime ; i++ ) {
    if( prime % i == 0 )
      return false ;

  } // for

  return true ;
} // isPrime()

void FindPrime( vector<Data> Alldata, int &prime ) {
  prime = Alldata.size()+1 ;
  while ( !isPrime(prime) ) {
    prime++ ;
  } // while
} // FindPrime()

void FindHashValue( char ID[], Hash atable[], int prime, int &hashkey ) {
  hashkey = ID[0] % prime ;
  for ( int i = 1 ; i < 16 ; i++ ) {
    if ( ID[i] >= 48 && ID[i] <= 57 )
      hashkey = hashkey * ID[i] % prime ;
  } // for
} // FindHashValue()

void BuildHash( vector<Data> &Alldata, Hash atable[], int prime, int hashkey ) {
  int gotime = 0 ; // 往下走了幾次，就等於碰撞幾次
  for( int i = 0 ; i < Alldata.size() ; i++ ) {
    FindHashValue( Alldata[i].studentID, atable, prime, hashkey ) ;
    if ( atable[hashkey].Hashvalue == -1 ) { // 這表示說雜湊表該放的位置是空的
      atable[hashkey].Hashvalue = hashkey ;
      strcpy(atable[hashkey].sID, Alldata[i].studentID );
      strcpy(atable[hashkey].sName, Alldata[i].studentName );
      atable[hashkey].Aver = Alldata[i].average ;
      atable[hashkey].collision = 1 ; // 預設只要沒有碰撞就放進去，就代表最佳情況只要搜尋一次
    } // if
    else { // 雜湊表裡面是有東西的

      int newhashkey = hashkey ;
      while ( atable[hashkey].Hashvalue != -1 ) {
        newhashkey++ ; // 就準備往下放，所以新增一個int值去紀錄要放的位置
        gotime++ ; // 還沒找到可以放的位置的時候，每往下走一次碰撞次數就要加一次
        if ( newhashkey == prime ) // 假設走到最後一個的話，有資料
          newhashkey = 0 ; // 就要回到一開始，再繼續找

        if ( atable[newhashkey].Hashvalue == -1 ) {
          atable[newhashkey].Hashvalue = hashkey ;
          strcpy( atable[newhashkey].sID, Alldata[i].studentID ) ;
          strcpy( atable[newhashkey].sName, Alldata[i].studentName ) ;
          atable[newhashkey].Aver = Alldata[i].average ;
          atable[newhashkey].collision = gotime+1 ; // 一定要搜尋過一次，加上我的碰撞次數
          break ;
        } // if
      } // while

       gotime = 0 ;
    } // else

  } // for

} // BuildHash()

void CountNotExist( Hash atable[], int prime, float & comparetime ) {
  int count = 0 ;
  bool isnull = false ; // 判斷是不是空的
  for ( int i = 0 ; i < prime ; i++ ) { // 每個位置都要算次數
    for ( int pos = i ; !isnull ; pos++ ) { // 算次數
      if ( atable[pos].Hashvalue == -1 )
        isnull = true ;
      else
        count++;

      if ( pos == prime-1 )
        pos = -1 ; // 因為往下跑的時候pos會剛好++，這樣0又+1了會變成1，0就沒有算到了
    } // for

    comparetime = comparetime + count ;
    count = 0 ;
    isnull = false ;
  } // for

  comparetime = comparetime / prime ;

} // CountNotExist()

void CountExist( vector<Data> Alldata, Hash atable[], int prime, float & exist ) {
  for ( int i = 0 ; i < prime ; i++ ) {
    exist = exist + atable[i].collision ;
  } // for

  exist = exist / Alldata.size() ;
} // CountExist()

void SaveAndOutput( Hash atable[], int prime, string fileName ) {
  fstream outfile;
  fileName = "Xoutput" + fileName + ".txt" ;
  outfile.open(fileName.c_str(), fstream::app) ;

  if ( !outfile.is_open() ) {
    cout << endl << fileName << " cannot be created!" << endl;
  } // if
  else {
    for ( int i = 0; i < prime; i++ ) {
      if ( atable[i].Hashvalue == -1 ) {
        outfile << "[" << i << "]" << endl ;
       } // if
       else {
         outfile << "[" << i << "]" << atable[i].Hashvalue << " , " << atable[i].sID << " , "
                 << atable[i].sName << " , " << atable[i].Aver << endl ;
       } // else
    } // for

  } // else
} // SaveAndOutput()

//-------------------------------------------------------------------------------------------------------------------------

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

void OutputHashTable(HashField *atable, int prime, string fileName)
{
  fstream outfile;
  fileName = "Doutputput" + fileName + ".txt" ;
  outfile.open(fileName.c_str(), fstream::app) ;

  if ( !outfile.is_open() ) {
    cout << endl << fileName << " cannot be created!" << endl;
  } // if
  else {
  	outfile << "--- Hash Table Y --- (double hashing)" << endl;
    for ( int i = 0; i < prime; i++ ) {
      if ( atable[i].hvalue == -1 ) {
        outfile << "[" << i << "]" << endl ;
       } // if
       else {
         outfile << "[" << i << "]" << atable[i].hvalue << " , " << atable[i].stuInfoStruct.sid << " , "
                 << atable[i].stuInfoStruct.sname << " , " << atable[i].stuInfoStruct.average << endl ;
       } // else
    } // for

  } // else
  
  return;
}

void CreateHashTable(vector<StuInfo> stuInfoVector, string fileName)
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
	
	OutputHashTable(hashTable, hashSize, fileName);
	
	free(hashTable);
	
	return;
}



void Procedure(string fileName)
{
	int len = 0; // store vector size, i.e. student infomations total number
	string filename = fileName;
    vector<StuInfo> stuInfoVectorReadFromFile; // store all the student information read from file
    string filenameHead = "input";
    string filenameEnd = ".dat";
	
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "Mission 2: Build a hash table by double hashing" << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl;
	while( ReadBinaryFile(stuInfoVectorReadFromFile, filenameHead + filename + filenameEnd).empty() ) // generate the input .txt file name
	{
		cout << filenameHead + filename + filenameEnd << " does not exist!!!" << endl << endl;
		cout <<"Input the file name (e.g., 500a, 501a, 502): [0]Quit" << endl;
		cin >> filename;
	}
	
	CreateHashTable(stuInfoVectorReadFromFile, filename);  // use all the student inforamtion read from file to create hash table 
	
	cin.ignore();
	
	return;	
}




 
int main() {
  int continueFlag = 0;
  int command = 0, prime = 0, hashkey = 0 ;
  float comparetime = 0.0, exist = 0.0 ;
  string fileName ;
  vector<Data> Alldata ;
  cout << "Input the filename (e.g.. 500a, 501a, 502): [0]Quit" << endl;
  cin >> fileName ;
  while ( fileName != "0" ) {
    comparetime = 0, exist = 0 ;
    getBinRecords( Alldata, fileName ) ;
    FindPrime( Alldata, prime ) ;
    Hash atable[prime] ;
    BuildHash( Alldata, atable, prime, hashkey ) ;
    SaveAndOutput( atable, prime, fileName ) ;
    cout << endl << "#########################################################" << endl;
    cout << "Mission 1: Build a hash table by linear probing" << endl;
    cout << "#########################################################" << endl << endl;
    cout << "Hash Table X is created" << endl << endl ;
    CountNotExist( atable, prime, comparetime ) ;
    CountExist( Alldata, atable, prime, exist ) ;
   // cout << "unsuccessful search: " << comparetime << " comparisons on average" << endl << endl;
    printf("unsuccessful search: %.4f comparisons on average\n\n\n", comparetime);
    printf("successful search: %.4f comparisons on average\n\n\n", exist);
    //cout << "successful search: " << exist << " comparisons on average" << endl << endl;

    Alldata.clear() ;
    
    Procedure(fileName);
    
    cout << "[0]Quit or [Any other key]continue?" << endl;
    scanf("%d", &continueFlag);
    if(continueFlag == 0)
    	return 0;
    else{
    	cout << "Input the filename (e.g.. 500a, 501a, 502): [0]Quit" << endl;
  		cin >> fileName ;
  	}
 //   cout << "Input a filename: " ;
  //  cin >> fileName ;
  } // while
}
