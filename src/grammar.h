#include <iostream>
#include <vector>
#include <map>
#include <set>

class Grammar {
public:
    std::map<char, int> index;  // index[S'] = 0
    std::string unterminal;
    std::string terminal;
    std::string alphabet;
    std::vector<std::vector<std::string>> rules;
    std::vector<std::pair<int, int>> rule_position;
    std::map<std::pair<int, int>, int> rule_num;

    Grammar(std::vector<std::string> &input);

    bool is_terminal(char x);

    int term_num(char x);

    std::set<char> FIRST(char x, std::vector<bool> &checked);
};
