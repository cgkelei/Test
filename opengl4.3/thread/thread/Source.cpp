#include <iostream>
#include <exception>
using namespace std;
class A
{
public:
	virtual void lock() = 0;
	virtual void unLock() = 0;
	virtual ~A(){};
};

class B :public A
{
public:
	B()
	{
		cout << "Construct B" << endl;
	}
	virtual ~B()
	{
		cout << "destory B" << endl;
	}
	virtual void lock()
	{
		cout << "Lock" << endl;
	}
	virtual void unLock()
	{
		cout << "UnLock" << endl;
	}
protected:
	int m_mutex;


};
int  main()
{			 
	B m_thread;
	m_thread.lock();
	m_thread.unLock();

	return 0;
}


