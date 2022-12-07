#include <iostream>
#include <vector>
#include <map>
#include <set>

class Grammar {
public:
    std::string unterminal; // all unterminal symbols of the grammar, starting with @ - added unterminal
    std::string terminal; // all terminal symbols of the grammar, ending with '$' - empty word
    std::string alphabet; // all symbols of grammar, alphabet = unterminal + terminal
    std::map<char, int> index;  // position of symbol in alphabet
    std::vector<std::vector<std::string>> rules; // all grammar rules,
    // for each rule [A -> alpha] we have rules[index[A]] = alpha
    std::vector<std::pair<int, int>> rule_position;  // coordinates of each rule in rules vector
    std::map<std::pair<int, int>, int> rule_num;  // rule number in the input file

    Grammar(std::vector<std::string> input);

    bool is_terminal(char x);

    int term_num(char x); // position of symbol in string "terminal"

    std::set<char> FIRST(char x, std::vector<bool> &checked);
};
