/**
 * Fancy console log output format
 * todo log level support
 *
 * @author Lukas Heiligenbrunner
 * @date 26.10.2019
 */

#pragma once

#include <string>

class Logger {
public:
    /**
     * a debug message
     * @param message message
     */
    static void debug(std::string message);

    /**
     * a default message
     * @param message message
     */
    static void message(std::string message);

    /**
     * a warning message
     * @param message message
     */
    static void warning(std::string message);

    /**
     * a error message
     * @param message message
     */
    static void error(std::string message);

    /**
     * a log message with manual level set
     * @param message message
     * @param level loglevel (1-4) or predefined labels
     */
    static void log(const std::string &message, int level);


    static const int Debug = 4;
    static const int Message = 3;
    static const int Warning = 2;
    static const int Error = 1;
};
