#include "situation.h"

int situation::after_dot(Grammar& gr) const {
    if(dot_position == gr.rules[left][right_index].size()) return -1;
    return gr.rules[left][right_index][dot_position];
}

int situation::rightside_length(Grammar& gr) const {
    return (gr.rules[left][right_index][0] == '$' ? 0 : gr.rules[left][right_index].size());
}

bool situation::is_final() const {
    return left == 0 && right_index == 0 && dot_position == 1 && word == '$';
}

bool operator <(const situation &a, const situation &b) {
    return a.left < b.left
    || a.left == b.left && a.right_index < b.right_index
    || a.left == b.left && a.right_index == b.right_index && a.word < b.word
    || a.left == b.left && a.right_index == b.right_index && a.word == b.word && a.dot_position < b.dot_position;
}

bool operator==(const situation &a, const situation &b) {
    return a.left == b.left && a.right_index == b.right_index
    && a.word == b.word && a.dot_position == b.dot_position;
}
