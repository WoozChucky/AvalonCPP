#include <Common/Logging/Log.h>

#include <Common/Utilities/StringConvert.h>
#include <Common/Utilities/Tokenize.h>
#include <Common/Utilities/Timer.h>
#include <Common/Logging/LogMessage.h>
#include <Common/Logging/LogOperation.h>
#include <Common/Logging/Logger.h>
#include <Common/Logging/Appender.h>
#include <Common/Logging/AppenderConsole.h>
#include <Common/Logging/AppenderFile.h>
#include <Common/Asio/Strand.h>

#include <memory>

Log::Log() : AppenderId(0), highestLogLevel(LOG_LEVEL_FATAL)
{
    m_logsTimestamp = "_" + GetTimestampStr();
    RegisterAppender<AppenderConsole>();
    RegisterAppender<AppenderFile>();
}

Log::~Log()
{
    delete _strand;
    Close();
}

U8 Log::NextAppenderId()
{
    return AppenderId++;
}

Appender* Log::GetAppenderByName(std::string_view name)
{
    auto it = appenders.begin();
    while (it != appenders.end() && it->second && it->second->getName() != name)
    {
        ++it;
    }

    return it == appenders.end() ? nullptr : it->second.get();
}


void Log::RegisterAppender(U8 index, AppenderCreatorFn appenderCreateFn)
{
    auto itr = appenderFactory.find(index);
    ASSERT(itr == appenderFactory.end());
    appenderFactory[index] = appenderCreateFn;
}

void Log::_outMessage(std::string const& filter, LogLevel level, std::string_view message)
{
    write(std::make_unique<LogMessage>(level, filter, message));
}

void Log::_outCommand(std::string_view message, std::string_view param1)
{
    write(std::make_unique<LogMessage>(LOG_LEVEL_INFO, "commands.gm", message, param1));
}

void Log::write(std::unique_ptr<LogMessage>&& msg) const
{
    Logger const* logger = GetLoggerByType(msg->type);

    if (_ioContext)
    {
        std::shared_ptr<LogOperation> logOperation = std::make_shared<LogOperation>(logger, std::move(msg));
        Avalon::Asio::post(*_ioContext, Avalon::Asio::bind_executor(*_strand, [logOperation]() { logOperation->call(); }));
    }
    else
        logger->write(msg.get());
}

Logger const* Log::GetLoggerByType(std::string const& type) const
{
    auto it = loggers.find(type);
    if (it != loggers.end())
    {
        return it->second.get();
    }

    if (type == LOGGER_ROOT)
    {
        return nullptr;
    }

    std::string parentLogger = LOGGER_ROOT;
    size_t found = type.find_last_of('.');
    if (found != std::string::npos)
    {
        parentLogger = type.substr(0, found);
    }

    return GetLoggerByType(parentLogger);
}

std::string Log::GetTimestampStr()
{
    return Avalon::Time::TimeToTimestampStr(GetEpochTime(), "%Y-%m-%d_%H_%M_%S");
}

bool Log::SetLogLevel(std::string const& name, S32 newLeveli, bool isLogger /* = true */)
{
    if (newLeveli < 0)
    {
        return false;
    }

    LogLevel newLevel = LogLevel(newLeveli);

    if (isLogger)
    {
        auto it = loggers.begin();
        while (it != loggers.end() && it->second->getName() != name)
        {
            ++it;
        }

        if (it == loggers.end())
        {
            return false;
        }

        it->second->setLogLevel(newLevel);

        if (newLevel != LOG_LEVEL_DISABLED && newLevel > highestLogLevel)
        {
            highestLogLevel = newLevel;
        }
    }
    else
    {
        Appender* appender = GetAppenderByName(name);
        if (!appender)
        {
            return false;
        }

        appender->setLogLevel(newLevel);
    }

    return true;
}

void Log::SetRealmId(U32 id)
{
    for (std::pair<U8 const, std::unique_ptr<Appender>>& appender : appenders)
    {
        appender.second->setRealmId(id);
    }
}

void Log::Close()
{
    loggers.clear();
    appenders.clear();
}

bool Log::ShouldLog(std::string const& type, LogLevel level) const
{
    /// @todo: Use cache to store "Type.sub1.sub2": "Type" equivalence, should
    // Speed up in cases where requesting "Type.sub1.sub2" but only configured
    // Logger "Type"

    // Don't even look for a logger if the LogLevel is higher than the highest log levels across all loggers
    if (level > highestLogLevel)
    {
        return false;
    }

    Logger const* logger = GetLoggerByType(type);
    if (!logger)
    {
        return false;
    }

    LogLevel logLevel = logger->getLogLevel();
    auto shouldLog = logLevel != LOG_LEVEL_DISABLED && logLevel >= level;
    return shouldLog;
}

Log* Log::Instance()
{
    static Log instance;
    return &instance;
}

void Log::Initialize(Avalon::Asio::IoContext* ioContext)
{
    if (ioContext)
    {
        _ioContext = ioContext;
        _strand = new Avalon::Asio::Strand(*ioContext);
    }

    LoadFromConfig();
}

void Log::SetSynchronous()
{
    delete _strand;
    _strand = nullptr;
    _ioContext = nullptr;
}

void Log::LoadFromConfig()
{
    Close();

    highestLogLevel = LOG_LEVEL_TRACE;
    AppenderId = 0;
    m_logsDir = "Logs";

    if (!m_logsDir.empty())
        if ((m_logsDir.at(m_logsDir.length() - 1) != '/') && (m_logsDir.at(m_logsDir.length() - 1) != '\\'))
        {
            m_logsDir.push_back('/');
        }

    _debugLogMask = DebugLogFilters(LOG_FILTER_NONE);

    auto appenderArgs = std::vector<std::string_view>();
    appenderArgs.push_back("1");
    appenderArgs.push_back("4");
    appenderArgs.push_back("0");
    appenderArgs.push_back("1 9 3 6 5 8");

    AppenderFlags flags = static_cast<AppenderFlags>(
            APPENDER_FLAGS_PREFIX_TIMESTAMP
            | APPENDER_FLAGS_PREFIX_LOGLEVEL
            | APPENDER_FLAGS_PREFIX_LOGFILTERTYPE
    );

    auto consoleAppender = std::make_unique<AppenderConsole>(0, "Console", LOG_LEVEL_TRACE, flags, appenderArgs);

    std::unique_ptr<Logger> logger = std::make_unique<Logger>(LOGGER_ROOT, LOG_LEVEL_TRACE);
    logger->addAppender(0, consoleAppender.get());

    appenders.insert(std::make_pair(0, consoleAppender.release()));
    loggers.insert(std::make_pair(LOGGER_ROOT, logger.release()));
}
