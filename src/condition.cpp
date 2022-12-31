#include "condition.h"

Condition::Condition(Grammar &gr) : gr(gr) {
    gamma = "";
    std::set<situation> unpredicted;
    situation first = {0, 0, 0, '$'};
    unpredicted.insert(first);
    predict(unpredicted);
}

Condition::Condition(Grammar &gr, Condition &prev_cond, char x) : gr(gr) {
    std::set<situation> unpredicted;
    gamma = prev_cond.gamma + x;
    for (situation sit: prev_cond.admissible) {
        if (sit.after_dot(gr) == x) {
            ++sit.dot_position;
            unpredicted.insert(sit);
        }
    }
    predict(unpredicted);
}

void Condition::find_possible_words(std::set<char>& possible_words, situation& sit) {
    std::string right = gr.rules[sit.left][sit.right_index];
    char f;
    int j = sit.dot_position;
    do {
        ++j;
        f = (j < right.size() ? right[j] : sit.word);
        std::vector<bool> checked(gr.unterminal.size(), false);
        possible_words = gr.FIRST(f, checked);
    } while (j < right.size() && gr.eps_gen[gr.index[f]]);
}

void Condition::predict(std::set<situation> &unpredicted) {
    std::set<char> possible_words;
    while (!unpredicted.empty()) {
        situation curr = *(unpredicted.begin());
        admissible.insert(curr);
        unpredicted.erase(curr);
        if (curr.after_dot(gr) == -1) continue;
        std::string right = gr.rules[curr.left][curr.right_index];
        char symbol = right[curr.dot_position];
        if (gr.is_terminal(symbol)) continue;
        find_possible_words(possible_words, curr);
        for (int j = 0; j < gr.rules[gr.index[symbol]].size(); ++j) {
            for (char x: possible_words) {
                situation new_sit = {gr.index[symbol], j, 0, x};
                if (admissible.find(new_sit) == admissible.end())
                    unpredicted.insert(new_sit);
            }
        }
    }
}


