#include <string>
#include <iostream>
using  namespace std;
int main(int argc, char **argv)
{
	string const str = "adfdasfas//adsfdsf//erfef//dsfdsfsd//bb.out";
	cout << str.find('o') << endl;;    //overload (char )
	cout << str.find("bbb") << endl;;
	 int n = str.find_last_of("//");
	 cout << str.substr(n+1) << endl;

	return 0;
}