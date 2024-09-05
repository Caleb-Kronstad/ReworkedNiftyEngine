#pragma once

#include "nfpch.h"

namespace Nifty
{
    class Log
    {
    public:
        template<typename T>
        static void Info(T msg)
        {
            std::cout << "\x1b[37m " << "[INFO] " << msg << "\x1b[37m\n";
        }

        template<typename T>
        static void Warning(T msg)
        {
            std::cout << "\x1b[33m " << "[WARNING] " << msg << "\x1b[37m\n";
        }

        template<typename T>
        static void Error(T msg)
        {
            std::cout << "\x1b[31m " << "[ERROR] " << msg << "\x1b[37m\n";
        }
    };
}