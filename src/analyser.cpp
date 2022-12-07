#include "analyser.h"

enum Actions {
    ACCESS,
    REDUCE,
    SHIFT,
    ERROR
};

int contains(std::vector<Condition> &set_of_conditions, Condition &cond) {
    for(int i = 0; i < set_of_conditions.size(); ++i) {
        if (set_of_conditions[i].admissible == cond.admissible) return i;
    }
    return -1;
}

Analyser::Analyser(Grammar &gr) : gr(gr) {
    std::deque<Condition> unpushed_conditions;
    unpushed_conditions.emplace_back(gr);
    while (!unpushed_conditions.empty()) {
        Condition pure = unpushed_conditions.front();
        GOTO.emplace_back(gr.alphabet.size(), -1);
        possible_conditions.push_back(pure);
        unpushed_conditions.pop_front();
        for (char x: gr.alphabet) {
            if(x == '$') continue;
            Condition new_made(gr, pure, x);
            if (new_made.admissible.empty()) continue;
            int num = contains(possible_conditions, new_made);
            if(num != -1) {
                GOTO.back()[gr.index[x]] = num;
                continue;
            }
            GOTO.back()[gr.index[x]] =
                    possible_conditions.size() + unpushed_conditions.size();
            unpushed_conditions.push_back(new_made);
        }
    }
    action_table = std::vector<std::vector<int>>(possible_conditions.size(),
             std::vector<int>(gr.terminal.size(), ERROR));
    std::set<char> possible_words;
    for (int i = 0; i < possible_conditions.size(); ++i) {
        for (situation sit: possible_conditions[i].admissible) {
            if (sit.is_final()) {
                action_table[i][gr.term_num(sit.word)] = ACCESS;
                continue;
            }
            if (sit.dot_position == sit.rightside_length(gr)) {
                if(action_table[i][gr.term_num(sit.word)] != ERROR) {
                    std::cerr << "Not LR(1) grammar!!!";
                }
                action_table[i][gr.term_num(sit.word)] = REDUCE;
                reduce_rule[{i, gr.index[sit.word]}] = {sit.left, sit.right_index};
            }
            else {
                std::string right = gr.rules[sit.left][sit.right_index];
                std::vector<bool> checked(gr.unterminal.size(), false);
                possible_words = gr.FIRST(right[sit.dot_position], checked);
                for(char x: possible_words) {
                    if(GOTO[i][gr.index[x]] == -1) continue;
                    if(action_table[i][gr.term_num(x)] != ERROR
                    && action_table[i][gr.term_num(x)] != SHIFT) {
                        std::cerr << "Not LR(1) grammar!!!";
                    }
                    else action_table[i][gr.term_num(x)] = SHIFT;
                }
            }
        }
    }
}

std::string Analyser::parse(std::string &word) {
    word += '$';
    std::stack<int> active_prefix;
    std::string result;
    int word_pos = 0;
    int current_condition = 0;
    active_prefix.push(current_condition);
    while (!active_prefix.empty() && word_pos < word.size()) {
        current_condition = active_prefix.top();
        char x = word[word_pos];
        int action = action_table[current_condition][gr.term_num(x)];
        if (action == ACCESS) return "YES " + result;
        if (action == REDUCE) {
            auto rule_pos = reduce_rule[{current_condition, gr.index[x]}];
            std::string right = gr.rules[rule_pos.first][rule_pos.second];
            for (int i = 0; i < (right[0] != '$' ? right.size() : 0); ++i) active_prefix.pop();
            current_condition = active_prefix.top();
            active_prefix.push(GOTO[current_condition][rule_pos.first]);
            result += std::to_string(gr.rule_num[{rule_pos.first, rule_pos.second}]);
        }
        if (action == SHIFT) {
            active_prefix.push(GOTO[current_condition][gr.index[x]]);
            ++word_pos;
        }
        if(action == ERROR) return "NO";
    }
    return "NOPE";
}

