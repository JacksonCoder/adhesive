#include "../include/execute.h"
#include <stdio.h> // for popen

// Taken from Stack Overflow:
// https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix

#if defined(_WIN32)
#define ADHESIVE_POPEN  _popen
#define ADHESIVE_PCLOSE _pclose
#else
#define ADHESIVE_POPEN  popen
#define ADHESIVE_PCLOSE pclose
#endif

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string           result;
    std::shared_ptr<FILE> pipe(ADHESIVE_POPEN(cmd, "r"), ADHESIVE_PCLOSE);

    if (!pipe) throw std::runtime_error("popen() failed!");

    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL) result += buffer.data();
    }

    return result;
}
