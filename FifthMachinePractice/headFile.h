
using namespace std;


vector<StuInfo>& ReadBinaryFile(vector<StuInfo> &, string);
void Procedure(string fileName);
bool JudgeIfPrime(int judgeNumber); // to determine whether a number is a prime number
void CreateHashTable(vector<StuInfo> stuInfoVector); // create a hash table function
double CalculateSidAscii(char* sid); // calculate sid each character ascii multiplication summation
