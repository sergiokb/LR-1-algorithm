#include <stack>
#include "condition.h"

int contains(std::vector<Condition> &set_of_conditions, Condition &cond);

class Analyser {
    Grammar &gr;
    std::vector<Condition> possible_conditions; // all conditions of this grammar
    std::vector<std::vector<int>> GOTO; // GOTO[i][x] - from condition i by symbol x, equals -1 if no transition
    std::vector<std::vector<int>> action_table; // action_table[i][index[c]] - action from condition i, peeking on c
                                                // action - one of: ACCESS, REDUCE, SHIFT, ERROR
    std::map<std::pair<int, int>, std::pair<int, int>> reduce_rule;
public:
    Analyser(Grammar &gr);

    std::string parse(std::string &word); // returns whether the word belongs to grammar
                                          // if it does, writes parsing of it (order or rules)
};
