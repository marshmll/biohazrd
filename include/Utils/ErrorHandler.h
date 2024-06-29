#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

#include <iostream>
#include <string>
using namespace std;

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
    void throwErr(string msg);

    /**
     * @brief Displays a error message on the console. Does
     * not exit the program.
     *
     * @note -> Does not exit program. Just prints a cerr.
     *
     * @param msg The message to be shown on the console.
     *
     * @return void.
     */
    void printErr(string msg);
};

#endif /* ERRORHANDLER_H */