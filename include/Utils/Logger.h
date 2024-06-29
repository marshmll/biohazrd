#ifndef LOGGER_H_
#define LOGGER_H_

#define LOGFOLDER "Logs/"

enum LogType
{
    DEBUG = 0,
    INFO,
    NOTICE,
    WARN,
    ERROR
};

class Logger
{
private:
    bool debugMode;

    stringstream logstream;
    string filename;

    map<LogType, string> logTypeTemplates;

    const string currentDateTime();

    void initLogTypeTemplates();

public:
    Logger(const bool debug = false);

    ~Logger();

    void begin();

    void end();

    void log(const string caller, const LogType log_type, const string log);
};

#endif /* LOGGER_H_ */