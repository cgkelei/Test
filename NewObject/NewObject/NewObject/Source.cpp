#include <iostream>
using namespace std;
class Person
{
public:
	explicit Person(int age, const char * name, double sales):
		_age(age), _sales(sales)
	{
		
		if (mystrlen(name) == 0)
			mystrcpy(_name, "HelloWorld");
		else
			mystrcpy(_name, name);
	}
	void Show()
	{
		cout << "Name:" << _name << "Age" << _age << "Sales;" << _sales << endl;
	}
	~Person()
	{
		_name[0]= '\0';
	}
public:
	int mystrlen(const char *str)
	{
		const char *pStr = str;
		while (*pStr++) ;
		return pStr - str - 1;
	}
	int mystrcmp(const char * str,const char *str2)
	{
		int n = 0;
		while (!(n = *(unsigned char*)str - *(unsigned char *)str2) && *str2)
			++str; ++str2;
		if (n < 0)
			n = -1;
		else if (n>0)
			n = 1;
		return n;
	}
	char* mystrcpy(char *source, const char *target)
	{
		char *pStr = source;
		while (*pStr++ = *target++);
		return source;
	}
	char* mystrcat( char * str,const char * str2)
	{
		char *pstr = str;
		while (*pstr);
		pstr++;
		while (*pstr++ = *str2++);
		return pstr;
	}

private:
	int _age;
	double _sales;
	char _name[100];
};
int main(int argc, char **argv)
{
	Person p(34, "½Ü½Ü", 1044.04f);
	p.Show();
	Person p1(50, "", 3434);
	p1.Show();
	

	//////////////////////////////////////////////////////////////////////////
	Person *p2;
	p2 = new Person(3434, "Ð¡·½", 343.004f);
	p2->Show();
	return 0;
}

