// test.cpp
#include "adhesive.h"

std::string f()
{
    return "Hello";
}

int main(int argc, char** argv)
{
    adhesive::a thing;
    thing.bind("thing", f);
    thing.handle(argc, argv);
    std::cout << thing.call("other_thing", "python", "test") << std::endl;
    return 0;
}
