#pragma once

#include <format>
#include <iostream>
#include <string>

namespace loguru {

class Logger {
public:
    enum class LogLevel {
        Error,
        Warn,
        Info,
        Debug
    };

    template<typename... Args>
    static void log(LogLevel level, const std::string& format_str, Args&&... args) {
        std::string colored_prefix;
        switch (level) {
            case LogLevel::Error:
                colored_prefix = "\033[31m[Error]\033[0m "; // Red
                break;
            case LogLevel::Warn:
                colored_prefix = "\033[33m[Warn]\033[0m ";  // Yellow
                break;
            case LogLevel::Info:
                colored_prefix = "[Info] ";  // Default (no color)
                break;
            case LogLevel::Debug:
                colored_prefix = "\033[36m[Debug]\033[0m ";  // Cyan
                break;
        }

        std::string message = std::format(format_str, std::forward<Args>(args)...);
        std::cout << colored_prefix << message << std::endl;
    }

    template<typename... Args>
    static void error(const std::string& format_str, Args&&... args) {
        log(LogLevel::Error, format_str, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void warn(const std::string& format_str, Args&&... args) {
        log(LogLevel::Warn, format_str, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void info(const std::string& format_str, Args&&... args) {
        log(LogLevel::Info, format_str, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void debug(const std::string& format_str, Args&&... args) {
        log(LogLevel::Debug, format_str, std::forward<Args>(args)...);
    }
};

} // namespace loguru

