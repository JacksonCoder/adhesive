// adhesive.h
#include <array>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>

#if defined(_WIN32)
#define ADHESIVE_POPEN  _popen
#define ADHESIVE_PCLOSE _pclose
#else
#define ADHESIVE_POPEN  popen
#define ADHESIVE_PCLOSE pclose
#endif

using namespace std;
std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string           result;
    std::shared_ptr<FILE> pipe(ADHESIVE_POPEN(cmd, "r"), ADHESIVE_PCLOSE);
    if (!pipe) throw std::runtime_error("ADHESIVE_POPEN() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL) result += buffer.data();
    }
    return result;
}
namespace adhesive {
    // template <typename t>
    class a {
    public:
        std::string call(std::string func, std::string lang, std::string target)  // lang should maybe be enum?
        {
            std::smatch matches;
            std::string res = exec(("./adhesive call " + func + " " + lang + " " + target).c_str());
            std::regex_search(res, matches, std::regex("_ADHESIVERETURN:\\(\\{\\[(.+)\\]\\}\\)"));
            return matches[1];
        }
        void bind(std::string value, std::function<std::string()> f) { bindlist[value] = f; }
        void handle(int argc, char** argv)
        {
            if (argc > 1) {
                if (std::string(argv[1]) == "___adhescall") {
                    std::string fcall = argv[2];
                    if (bindlist.find(fcall) == bindlist.end()) {
                        std::cout << "ADHESERROR:(Function not bound)" << std::endl;
                    }
                    else
                        std::cout << "_ADHESIVERETURN:({[" << bindlist[fcall]() << "]})";  // find better method to output
                    exit(0);
                }
            }
        }

    private:
        std::map<std::string, std::function<std::string()>> bindlist;
    };
};
