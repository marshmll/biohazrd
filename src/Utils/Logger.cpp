#include "stdafx.h"
#include "Logger.h"

const string Logger::currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void Logger::initLogTypeTemplates()
{
    logTypeTemplates[DEBUG] = "(DEBUG) ";
    logTypeTemplates[INFO] = "(INFO) ";
    logTypeTemplates[NOTICE] = "(NOTICE) ";
    logTypeTemplates[WARN] = "(WARN) ";
    logTypeTemplates[ERROR] = "(ERROR) ";
}

Logger::Logger(const bool debug)
{
    debugMode = debug;
}

Logger::~Logger()
{
    end();
}

void Logger::begin()
{
    initLogTypeTemplates();

    time_t start = chrono::system_clock::to_time_t(chrono::system_clock::now());

    string file_date = ctime(&start);
    file_date.erase(remove(file_date.begin(), file_date.end(), '\n'), file_date.cend());

    filename = "Logs/" + file_date + ".txt";

    if (debugMode)
        logstream << "[DEBUG MODE ENABLED] =================================================================================================" << "\n";
}

void Logger::end()
{
    // ofstream ofs;
    // ofs.open(filename, ios::out);

    // if (!ofs.is_open())
    //     ErrorHandler::throwErr("LOGGER::END::ERR_COULD_NOT_OPEN_FILE: " + filename);

    // ofs << logstream.str();

    // ofs.close();

    // cout << "wrote logs to file: " << filename << "\n";
}

void Logger::log(const string caller, const LogType log_type, const string log)
{
    if (log_type == DEBUG && !debugMode)
        return;

    logstream << currentDateTime() << " [" << caller << "] > " << logTypeTemplates[log_type] << log << "\n";

    if (log_type == ERROR)
        end();
}
