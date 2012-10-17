#include "libap2p/log/log.hpp"

using namespace libap2p;

int main()
{
    Log::SetVerbosity(21);
    Log::Push(LogLevel::ERROR, "Log entry = error"); // Error test
    Log::Push(LogLevel::WARNING, "Log entry = warning"); //Warning test
}
