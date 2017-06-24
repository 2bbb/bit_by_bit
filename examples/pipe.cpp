#include <bbb/pipe.hpp>
#include <bbb/logger.hpp>

#include <string>
#include <vector>
#include <array>
#include <map>

bbb::custom_logger<bbb::simple_header> logger;

int main() {
    std::string str = "foo_bar";
    logger("split by _ and join with /") << (str | bbb::split("_") | bbb::join("/"));
    logger("apply toupper") << (str | bbb::upper());
    logger("| is immutable") << str;
    logger("apply toupper with |=") << (str |= bbb::upper());
    logger("| is destructive") << str;
    logger("overloaded char *") << ("camel_case" | bbb::camelize());
    logger.br();
    
    logger("map");
    std::vector<int> xs{1, 2, 3, 4};
    for(auto x : xs | bbb::map([](int x) { return 2 * x; })) {
        logger() << x;
    }
    logger.br();
    
    logger("map for array with different type");
    std::array<int, 4> ys{1, 2, 3, 4};
    for(auto x : ys | bbb::map([](int x) { return 2.34 * x; })) {
        logger() << x;
    }
    logger.br();
    
    std::map<std::string, int> hash{
        {"first", 1},
        {"second", 2},
        {"third", 3},
        {"fourth", 4}
    };
    
    logger("get keys");
    for(auto &key : hash | bbb::keys()) {
        logger() << key;
    }
    logger.br();
   
    logger("get values");
    for(auto &v : hash | bbb::values()) {
        logger() << v;
    }
}