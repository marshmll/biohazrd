#ifndef LOGGER_H_
#define LOGGER_H_

#define LOGFOLDER "Logs/"

enum LOGTYPE
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

    std::stringstream logstream;
    std::string filename;

    std::map<LOGTYPE, std::string> logTypeTemplates;

    const std::string currentDateTime();

    void initLogTypeTemplates();

public:
    Logger(const bool debug = false);

    ~Logger();

    void begin();

    void end();

    void log(const std::string caller, const LOGTYPE log_type, const std::string log);
};

#endif /* LOGGER_H_ */