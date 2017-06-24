#include <bbb/type/notifier.hpp>
#include <bbb/logger.hpp>
#include <bbb/pipe.hpp>

#include <string>
#include <iostream>
#include <algorithm>

bbb::custom_logger<bbb::simple_header> logger;

int main(int argc, char *argv[]) {
    bbb::notifier<int> m;
    m.value_will_change([](int x) { logger("n") << "will change from: " << x; });
    m.value_did_change([](int x) { logger("n") << "n did change to: " << x; });
    m = 8;
    
    bbb::notifier<int> n{
        [](int x) { logger("m") << "will change from: " << x; },
        [](int x) { logger("m") << "did change to: " << x; }
    };
    n = 4;
    n++;
    
    bbb::notifier<std::string> str{
        "hoge",
        [](const std::string &str) { logger("str") << "will change from: " << str; },
        [](const std::string &str) { logger("str") << "did change to: " << str; }
    };
    
    str += str;
    str[0] = 'H';
    
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}