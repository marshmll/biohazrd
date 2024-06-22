#include "ErrorHandler.h"

void ErrorHandler::throwErr(std::string msg)
{
    std::cerr << "ERRORHANDLER::THROWERR::" << msg << "\n";
    exit(EXIT_FAILURE);
}
