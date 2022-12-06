#include <vector>
#include <map>
#include <set>
#include "situation.h"

class Condition {
    Grammar &gr;
public:
    std::string gamma;
    std::set<situation> admissible;
private:
    void get_possible_words(std::set<char> &possible_words, situation &sit);

    void predict(std::set<situation> &unpredicted);

public:
    Condition(Grammar &gr);

    Condition(Grammar &gr, Condition &prev_cond, char x);
};


