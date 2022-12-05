enum Actions {
    ACCESS,
    REDUCE,
    SHIFT,
    ERROR
};

class Analyser {
    Grammar &grammar;
    std::vector<Condition> possible_conditions;
    std::vector<std::vector<int>> transition_table;
    std::vector<std::vector<int>> action_table;
    std::map<std::pair<int, int>, std::pair<int, int>> reduce_rule;
public:
    Analyser(Grammar &grammar) : grammar(grammar) {
        std::deque<Condition> unpushed_conditions;
        unpushed_conditions.emplace_back(grammar);
        while (!unpushed_conditions.empty()) {
            Condition pure = unpushed_conditions.front();
            transition_table.emplace_back(grammar.alphabet.size() + 1, -1); // ou
            possible_conditions.push_back(pure);
            unpushed_conditions.pop_front();
            for (char x: grammar.alphabet) {
                Condition new_made(grammar, pure, x);
                if (new_made.admissible.empty()) continue;
                int num = contains(possible_conditions, new_made);
                if(num != -1) {
                    transition_table.back()[grammar.index[x]] = num;
                    continue;
                }
                transition_table.back()[grammar.index[x]] =
                        possible_conditions.size() + unpushed_conditions.size();
                unpushed_conditions.push_back(new_made);
            }
        }
        action_table = std::vector<std::vector<int>>
                (possible_conditions.size(),
                 std::vector<int>(grammar.alphabet.size() + 2, SHIFT)); // not what we want
        for (int i = 0; i < possible_conditions.size(); ++i) {
            for (situation sit: possible_conditions[i].admissible) {
                //if (action_table[i][grammar.index[sit.word]] != ERROR) continue;
//                    std::cerr << "Not LR(1) grammar!!!";
                if (sit.left == 0 && sit.right_index == 0
                    && sit.dot_position == 1 && sit.word == '$') {
                    action_table[i][grammar.index[sit.word]] = ACCESS;
                    continue;
                }
                if(i == 2) {
                    i = 2;
                }
                if (sit.dot_position == (grammar.rules[sit.left][sit.right_index][0] != '$'
                ? grammar.rules[sit.left][sit.right_index].size() : 0)) {
                    action_table[i][grammar.index[sit.word]] = REDUCE;
                    reduce_rule[{i, grammar.index[sit.word]}] = {sit.left, sit.right_index};
                }
//                else {
//                    std::string right = grammar.rules[sit.left][sit.right_index];
//                    char symbol = right[sit.dot_position];
//                    if (symbol >= 'a' || symbol == '$') continue;
//                    std::string b2 = (sit.dot_position + 1 == right.size() ? "" :
//                            right.substr(sit.dot_position + 1,
//                                         right.size() - sit.dot_position));
//                    std::vector<bool> checked(grammar.un_terms.size(), false);
//                    std::set<char> possible_words =
//                            possible_conditions[i].FIRST(b2 + sit.word, checked);
//                    if(possible_words.find(grammar.index[sit.word]) != possible_words.end())
//                        action_table[i][grammar.index[sit.word]] = SHIFT;
//                }
            }
        }
    }

    std::string parse(std::string &word) {
        word += '$';
        std::stack<int> active_prefix;
        std::string result;
        int position = 0;
        int current_condition = 0;
        active_prefix.push(current_condition);
        while (!active_prefix.empty() && position < word.size()) {
            current_condition = active_prefix.top();
            char x = word[position];
            int y = action_table[current_condition][grammar.index[x]];
            if (y == ACCESS) return "YES " + result;
            //if (y == ERROR) return "NO";
            if (y == SHIFT) {
                int new_cond = transition_table[current_condition][grammar.index[x]];
                if(new_cond != -1) {
                    active_prefix.push(transition_table[current_condition][grammar.index[x]]);
                    ++position;
                }
                else return "NO";
            }
            if (y == REDUCE) {
                auto p = reduce_rule[{current_condition, grammar.index[x]}];
                int left = p.first;
                std::string right = grammar.rules[left][p.second];
                for (int i = 0; i < (right[0] != '$' ? right.size() : 0); ++i) active_prefix.pop();
                current_condition = active_prefix.top();
                active_prefix.push(transition_table[current_condition][left]);
                result += std::to_string(left) += std::to_string(p.second);
                result += " <- ";
            }
        }
        return "NOPE";
    }
};
