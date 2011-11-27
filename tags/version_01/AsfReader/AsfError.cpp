#include "StdAfx.h"
#include "AsfError.h"

namespace Asf {

void error(const char* why, const char* what)
	// throws runtime exception
{
	throw std::runtime_error(std::string(why) + std::string(what));
}

void error(const std::string& why, const std::string& what)
	// throws runtime exception
{
	throw std::runtime_error(why + what);
}

} //end of namespace
