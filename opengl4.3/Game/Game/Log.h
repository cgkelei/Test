
#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string>
#include <vector>
class Log
{
public:
	Log();
	~Log();
	static void SetLog( std::string log );
	static void PrintLog();
private:
	static std::vector<std::string> m_log;



};
#endif // !LOG_H
