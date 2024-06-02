#include "ErrorHandler.h"

void ErrorHandler::throwErr(std::string msg)
{
    std::cerr << "ERRORHANDLER::THROWERR::" << msg;
    exit(EXIT_FAILURE);
}
