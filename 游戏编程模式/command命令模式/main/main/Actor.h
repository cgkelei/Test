#pragma once
#include "iostream"
using namespace  std;
class Actor
{
public:
	Actor(){}
	virtual ~Actor(){};
public:
	virtual void jump() = 0;
	virtual void run() = 0;
	virtual void fire() = 0;
};
class human : public Actor
{
public:
	human() { cout << "hi man" << endl; }
	~human(){}
	void jump(){ cout << "Man Jump" << endl; }
	void run(){ cout << "Man Run" << endl; }
	void fire(){ cout << "Man Fire" << endl; }
};
class sprite :public Actor
{
public:
	sprite() { cout << "hi sprite" << endl; }
	~sprite(){}
	void jump(){ cout << "Man sprite" << endl; }
	void run(){ cout << "sprite Run" << endl; }
	void fire(){ cout << "sprite Fire" << endl; }
};
class beast :public Actor
{
public:
	beast() { cout << "hi beast" << endl; }
	~beast(){}
	void jump(){ cout << "beast Jump" << endl; }
	void run(){ cout << "beast Run" << endl; }
	void fire(){ cout << "beast Fire" << endl; }
};


