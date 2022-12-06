class Grammar {
public:
    std::map<char, int> index;  // index[S'] = 0
    std::string unterminal;
    std::string terminal;
    std::string alphabet;
    std::vector<std::vector<std::string>> rules;
    std::vector<std::pair<int, int>> rule_position;
    std::map<std::pair<int, int>, int> rule_num;

    Grammar(std::vector<std::string> &input) {
        input[0].insert(0, "@ -> ");   // S' -> S
        for (std::string &line : input) {
            char left = line[0];
            std::string right = line.substr(5, line.size() - 5);
            if (index.find(left) == index.end()) {
                index[left] = rules.size();
                unterminal += left;
                rules.emplace_back();
            }
            rule_num[{index[left], rules[index[left]].size()}] = rule_position.size();
            rule_position.emplace_back(index[left], rules[index[left]].size());
            rules[index[left]].push_back(right);
        }
        alphabet = unterminal;
        for(int i = 0; i < rules.size(); ++i) {
            for(const std::string& right: rules[i]) {
                for (char x: right) {
                    if(x == '$') continue;
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

    bool is_terminal(char x) {
        return index[x] >= unterminal.size();
    }

    int term_num(char x) {
        return index[x] - unterminal.size();
    }

    std::set<char> FIRST(char x, std::vector<bool> &checked) {
        std::set<char> ans;
        if (is_terminal(x)) {
            ans.insert(x);
            return ans;
        }
        if (checked[index[x]]) return ans;
        checked[index[x]] = true;
        for (const std::string &right: rules[index[x]]) {
            std::set<char> gotten = FIRST(right[0], checked);
            ans.insert(gotten.begin(), gotten.end());
        }
        return ans;
    }
};
