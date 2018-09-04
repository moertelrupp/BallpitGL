#pragma once

// Includes
#include "UppIncludes.hpp"

namespace upp
{
    class UppException
    {
    public:
        UppException(std::string msg, std::string filename, int line)
        {
            this->msg = trimFilename(filename) + " #" + std::to_string(line) + ": " + msg;
        }

        void propagate(std::string msg, std::string filename, int line)
        {
            this->msg = this->msg + "\r\n" + trimFilename(filename) + " #" + std::to_string(line) + ": " + msg;
        }

        void printMsg()
        {
            std::cout << "ERROR!" << std::endl << msg << std::endl;
        }

        std::string getMsg()
        {
            return msg;
        }

    private:
        std::string msg;

        std::string trimFilename(std::string filename)
        {
            // Trim to only Filename, not full path to file
            int last = 0;
            bool found = false;
            for (int i = 0; i < filename.length(); i++)
            {
                if (filename[i] == '\\')
                {
                    found = true;
                    last = i;
                }
            }

            if (found)
            {
                filename = filename.substr(last + 1, std::string::npos);
            }

            // Uppercase first letter
            if (filename.length() > 0)
            {
                if (filename[0] > 96)
                {
                    filename[0] = filename[0] - 32;
                }
            }

            return filename;
        }
    };
}
