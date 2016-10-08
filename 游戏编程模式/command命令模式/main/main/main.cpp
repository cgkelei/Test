//这是一份最都认原始的命令模式，在真正的项目中不会这样写，现在的目的只是用于清晰思路
//kelei

#include <iostream>
#include "Actor.h"
using namespace  std;

class command
{
public:
	command(){}
	~command(){}
	virtual void excute( Actor &actor ) = 0;

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
	virtual void excute( Actor &actor )
	{
		actor.fire();
	}

};
class jump :public command
{
public:
	jump(){ cout << "jump construction" << endl; }
	~jump(){ cout << "jump destruction" << endl; }
	virtual void excute( Actor &actor ){ actor.jump(); }
};
class run :public command
{
public:
	run(){ cout << "run consturction" << endl; }
	~run(){ cout << "destruction" << endl; }
	virtual void excute( Actor &actor ){ actor.run(); }
};
class inputHandle
{
public:
	inputHandle(){
		m_Cfrie = new fire();
		m_Cjump = new jump();
		m_Crun = new run();
	}
	command* handle( char key )
	{
		switch (key)
		{
		case '1':
			return m_Cfrie;
			break;
		case '2':
			return m_Cjump;
			break;
		case '3':
			return m_Crun;
			break;
		default:
			break;
		}
		return NULL;
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
#include "Actor.h"
	Actor *pActor= new human;
	command *pCommand = NULL;
	do 
	{
		cin >> key;
		if (key =='9')
		{
			pActor = new human;
		}
		else if (key == '8')
		{
			pActor = new sprite;
		}
		else if (key == '7')
		{
			pActor = new beast;
		}
		else
		{
			

		}
		cin >> key;
		pCommand = aa->handle( key );
		if (pCommand!=NULL)
		{
			pCommand->excute(*pActor);
		}
	
	} while (key != '0');

	delete pActor;
	delete pCommand;
	delete aa;
	delete aa;
	return 0;
}