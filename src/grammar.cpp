#include "grammar.h"

Grammar::Grammar(std::vector<std::string> input) {
    input[0].erase(0, strlen("Starting with: "));
    input[0].insert(0, "0. @ -> ");   // S' -> S
    for (std::string &line : input) {
        line.erase(0, line.find('.') + 2);
        char left = line[0];
        line.erase(0, strlen("A -> "));
        if (index.find(left) == index.end()) {
            index[left] = rules.size();
            unterminal += left;
            rules.emplace_back();
        }
        rule_num[{index[left], rules[index[left]].size()}] = rule_position.size();
        rule_position.emplace_back(index[left], rules[index[left]].size());
        rules[index[left]].push_back(line);
    }
    alphabet = unterminal;
    eps_gen.assign(unterminal.size(), false);
    for(int i = 0; i < rules.size(); ++i) {
        for(const std::string& right: rules[i]) {
            for (char x: right) {
                if(x == '$') {
                    eps_gen[i] = true;
                    continue;
                }
                if (index.find(x) == index.end()) {
                    index[x] = alphabet.size();
                    alphabet += x;
                }
            }
        }
    }
    index['$'] = alphabet.size();
    alphabet += '$';
    terminal = alphabet.substr(unterminal.size(), alphabet.size() - unterminal.size());
}

bool Grammar::is_terminal(char x) {
    return index[x] >= unterminal.size();
}

int Grammar::term_num(char x) {
    return index[x] - unterminal.size();
}

std::set<char> Grammar::FIRST(char x, std::vector<bool> &checked) {
    std::set<char> ans;
    if (is_terminal(x)) {
        ans.insert(x);
        return ans;
    }
    if (checked[index[x]]) return ans;
    checked[index[x]] = true;
    for (const std::string &right: rules[index[x]]) {
        int j = -1;
        do {
            ++j;
            std::set<char> gotten = FIRST(right[j], checked);
            ans.insert(gotten.begin(), gotten.end());
        } while (eps_gen[index[right[j]]]);
    }
    return ans;
}

