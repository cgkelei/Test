#include "Log.h"
#include <iomanip>
std::vector<std::string> Log::m_log;
Log::Log()
{
}


Log::~Log()
{
}

void Log::SetLog( std::string log )
{
	m_log.push_back( log );
}

void Log::PrintLog( )
{
	std::cout << std::setfill(' ') <<"info:"<<std::endl;
	for (size_t i = 0; i < m_log.size();i++)
	 {
		 std::cout << std::setw( 5 ) << i << ":\t"<< m_log[i] << std::endl;
		 //m_log.pop_front();
	 }

}

