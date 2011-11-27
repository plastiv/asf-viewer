#pragma once
#include <string>

namespace Asf {

// no classes, just functions for hadling error messages
void error(const char* why, const char* what="");
void error(const std::string& why, const std::string& what="");
}
