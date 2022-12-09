#include <vector>
#include <map>
#include <set>
#include "situation.h"

class Condition {
    Grammar &gr;
public:
    std::string gamma; // postfix of active prefix
    std::set<situation> admissible; // situations in this condition
private:
    void find_possible_words(std::set<char> &possible_words, situation &sit);
    // for situation [A -> alpha.Bbeta, u] finds FIRST(betau)

    void predict(std::set<situation> &unpredicted); // finds closure, puts to admissible

public:
    Condition(Grammar &gr);

    Condition(Grammar &gr, Condition &prev_cond, char x); // GOTO(previous condition) by x
};


