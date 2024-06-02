#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

#include <iostream>
#include <string>

/**
 * @brief Namespace for custom error handling.
 *
 */
namespace ErrorHandler
{
    /**
     * @brief Displays a error message on the console and
     * exit with EXIT_FAILURE status.
     *
     * @note -> Ends program with EXIT_FAILURE.
     *
     * @param msg The message to be shown on the console.
     *
     * @return void.
     */
    void throwErr(std::string msg);
};

#endif /* ERRORHANDLER_H */