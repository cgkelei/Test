//这是一份最都认原始的命令模式，在真正的项目中不会这样写，现在的目的只是用于清晰思路
//kelei

#include <iostream>
using namespace  std;

class command
{
public:
	command(){}
	~command(){}
	virtual void excute() = 0;
};
class fire :public command
{
public:
	fire()
	{
		cout << "Fire Construction" << endl;
	}
	~fire()
	{
		cout << "Fire Destruction" << endl;
	}
	virtual void excute()
	{
		cout << "..........Fire" << endl;
	}

};
class jump :public command
{
public:
	jump(){ cout << "jump construction" << endl; }
	~jump(){ cout << "jump destruction" << endl; }
	virtual void excute(){ cout << "..............jump" << endl; }
};
class run :public command
{
public:
	run(){ cout << "run consturction" << endl; }
	~run(){ cout << "destruction" << endl; }
	virtual void excute(){ cout << "............run" << endl; }
};
class inputHandle
{
public:
	inputHandle(){
		m_Cfrie = new fire();
		m_Cjump = new jump();
		m_Crun = new run();
	}
	void handle( char key )
	{
		switch (key)
		{
		case '1':
			m_Cfrie->excute();
			break;
		case '2':
			m_Cjump->excute();
			break;
		case '3':
			m_Crun->excute();
			break;
		default:
			break;
		}
	}
	~inputHandle(){};
private:
	fire * m_Cfrie;
	jump * m_Cjump;
	run * m_Crun;
};
int  main( int argc, char*argv[] )
{
	char key;
	inputHandle *aa = new inputHandle;
	do 
	{
		cin >> key;
		aa->handle( key );
		
	} while (key != '0');
	delete aa;
	return 0;
}