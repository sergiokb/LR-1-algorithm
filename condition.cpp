struct situation {
    int left;
    int right_index;
    int dot_position;
    char word;
};

auto situations_cmp = [](const situation &a, const situation &b) {
    return a.left < b.left
           || a.left == b.left && a.right_index < b.right_index
           || a.left == b.left && a.right_index == b.right_index && a.word < b.word
           || a.left == b.left && a.right_index == b.right_index && a.word == b.word && a.dot_position < b.dot_position;
};

bool operator==(const situation &a, const situation &b) {
    return a.left == b.left && a.right_index == b.right_index
           && a.word == b.word && a.dot_position == b.dot_position;
};

class Condition {
    Grammar &gr;
public:
    std::string gamma;
    std::set<situation, decltype(situations_cmp)> admissible;

    Condition(Grammar &gr) : gr(gr) {
        std::set<situation, decltype(situations_cmp)> unpredicted;
        gamma = "";
        situation first = {0, 0, 0, '$'};
        unpredicted.insert(first);
        predict(unpredicted);
    }

    Condition(Grammar &gr, Condition &prev_cond, char x) : gr(gr) {
        std::set<situation, decltype(situations_cmp)> unpredicted;
        gamma = prev_cond.gamma + x;
        for (situation sit: prev_cond.admissible) {
            if (sit.dot_position == gr.rules[sit.left][sit.right_index].size()) continue;
            if (gr.rules[sit.left][sit.right_index][sit.dot_position] == x) {
                ++sit.dot_position;
                unpredicted.insert(sit);
            }
        }
        predict(unpredicted);
    }

    std::set<char> FIRST(const std::string &w, std::vector<bool> &checked) {
        std::set<char> ans;
        char first = w[0];
        if (first >= 'a' || first == '$') {
            ans.insert(first);
            return ans;
        }
        if (checked[gr.index[first]]) return ans;
        checked[gr.index[first]] = true;
        for (const std::string &right: gr.rules[first]) {
            std::set<char> gotten = FIRST(right, checked);
            ans.insert(gotten.begin(), gotten.end());
        }
        return ans;
    }

    void predict(std::set<situation, decltype(situations_cmp)> &unpredicted) {
        while (!empty(unpredicted)) {
            situation curr = *(unpredicted.begin());
            admissible.insert(curr);
            unpredicted.erase(curr);
            if (curr.dot_position == gr.rules[curr.left][curr.right_index].size()) continue;
            std::string right = gr.rules[curr.left][curr.right_index];
            char symbol = right[curr.dot_position];
            if (symbol >= 'a' || symbol == '$') continue;
            std::string b2 = (curr.dot_position + 1 == right.size() ? "" :
                              right.substr(curr.dot_position + 1,
                                           right.size() - curr.dot_position));
            std::vector<bool> checked(gr.un_terms.size(), false);
            std::set<char> possible_words = FIRST(b2 + curr.word, checked);
            for (int j = 0; j < gr.rules[gr.index[symbol]].size(); ++j) {
                for (char u: possible_words) {
                    situation new_sit = {gr.index[symbol], j, 0, u};
                    if (admissible.find(new_sit) == admissible.end())
                        unpredicted.insert(new_sit);
                }
            }

        }
    }
};

int contains(std::vector<Condition> &set_of_conditions, Condition &cond) {
    for(int i = 0; i < set_of_conditions.size(); ++i) {
        if (set_of_conditions[i].admissible == cond.admissible) return i;
    }
    return -1;
}

