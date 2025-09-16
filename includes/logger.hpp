#pragma once
#include <string>
#include <fstream>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

class Logger
{
private:
    string filename;

    static string currentDateTime()
    {
        time_t now = time(nullptr);
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return string(buf);
    }

public:
    Logger(const string &file = "system.log") : filename(file) {}

    void log(const string &message)
    {
        ofstream out(filename, ios::app);
        if (out.is_open())
        {
            out << "[" << currentDateTime() << "] " << message << endl;
            out.flush();
            out.close();
        }
        else
        {
            cerr << "Logger ERROR: cannot open " << filename << " for writing\n";
        }
    }

    void logError(const string &message)
    {
        const string authFile = "Authentication.log";
        ofstream outErr(authFile, ios::app);
        if (outErr.is_open())
        {
            outErr << "[" << currentDateTime() << "] ERROR: " << message << endl;
            outErr.flush();
            outErr.close();
        }
        else
        {
            cerr << "Logger ERROR: cannot open " << authFile << " for writing\n";
        }

        ofstream outMain(filename, ios::app);
        if (outMain.is_open())
        {
            outMain << "[" << currentDateTime() << "] ERROR: " << message << endl;
            outMain.flush();
            outMain.close();
        }
        else
        {
            cerr << "Logger ERROR: cannot open " << filename << " for writing (secondary)\n";
        }

        cerr << "Logger: logged error -> " << message << "\n";
    }

    static void logTo(const string &message, const string &file = "system.log")
    {
        ofstream out(file, ios::app);
        if (out.is_open())
        {
            time_t now = time(nullptr);
            char buf[64];
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
            out << "[" << buf << "] " << message << endl;
            out.flush();
            out.close();
        }
        else
        {
            cerr << "Logger.logTo: cannot open " << file << " for writing\n";
        }
    }
};