class Grammar {
public:
    std::map<char, int> index;  // index[S'] = 0
    std::string un_terms;
    std::string terminal;
    std::string alphabet;
    std::vector<std::pair<int, int>> rule_position;
    std::vector<std::vector<std::string>> rules;

    Grammar(std::vector<std::string> &input) {
        input[0].insert(0, "@ -> ");   // S' -> S
        for (std::string &line : input) {
            char left = line[0];
            std::string right = line.substr(5, line.size() - 5);
            if (index.find(left) == index.end()) {
                index[left] = rules.size();
                un_terms += left;
                rules.emplace_back();
            }
            rule_position.emplace_back(index[left], rules[index[left]].size());
            rules[index[left]].push_back(right);
        }
        for(int i = 0; i < rules.size(); ++i) {
            for(const std::string& right: rules[i]) {
                for (char x: right) {
                    if(x == '$') continue;
                    if (index.find(x) == index.end()) {
                        index[x] = un_terms.size() + terminal.size();
                        terminal += x;
                    }
                }
            }
        }
        alphabet = un_terms + terminal;
        index['$'] = alphabet.size();
        alphabet = alphabet.substr(1, alphabet.size() - 1);
        terminal += '$';
    }
};