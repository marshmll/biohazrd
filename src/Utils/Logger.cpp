#include "stdafx.h"
#include "Logger.h"

const std::string Logger::currentDateTime()
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

Logger::Logger() {}

Logger::~Logger()
{
    end();
}

void Logger::begin()
{
    initLogTypeTemplates();

    std::time_t start = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string file_date = std::ctime(&start);
    file_date.erase(std::remove(file_date.begin(), file_date.end(), '\n'), file_date.cend());

    filename = "Logs/" + file_date + ".txt";
}

void Logger::end()
{
    std::ofstream ofs;
    ofs.open(filename, std::ios::out);

    if (!ofs.is_open())
        ErrorHandler::throwErr("LOGGER::END::ERR_COULD_NOT_OPEN_FILE: " + filename);

    ofs << logstream.str();

    ofs.close();

    std::cout << "wrote logs to file: " << filename << "\n";
}

void Logger::log(const std::string caller, const LOGTYPE log_type, const std::string log)
{
    logstream << currentDateTime() << " [" << caller << "] > " << logTypeTemplates[log_type] << log << "\n";

    if (log_type == ERROR)
        end();
}
