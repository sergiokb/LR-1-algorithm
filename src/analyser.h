#include <stack>
#include "condition.h"

int contains(std::vector<Condition> &set_of_conditions, Condition &cond);

class Analyser {
    Grammar &gr;
    std::vector<Condition> possible_conditions;
    std::vector<std::vector<int>> GOTO;
    std::vector<std::vector<int>> action_table;
    std::map<std::pair<int, int>, std::pair<int, int>> reduce_rule;
public:
    Analyser(Grammar &gr);

    std::string parse(std::string &word);
};
