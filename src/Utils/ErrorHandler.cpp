#include "ErrorHandler.h"

void ErrorHandler::throwErr(string msg)
{
    cerr << "ERRORHANDLER::THROWERR::" << msg << "\n";
    exit(EXIT_FAILURE);
}

void ErrorHandler::printErr(string msg)
{
    cerr << "ERRORHANDLER::PRINTERR::" << msg << "\n";
}
