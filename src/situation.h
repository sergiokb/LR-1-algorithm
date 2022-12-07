#include "grammar.h"

struct situation {
    // Situation looks like: [A -> beta1.beta2, word]
    int left; // index[A]
    int right_index; // index of beta1beta2 in rules[A]
    int dot_position; // position af a dot in rightside, equals length(beta1)
    char word; // peeking word, in case of LR(1) - symbol

    int after_dot(Grammar &gr) const; // index of symbol after dot

    int rightside_length(Grammar &gr) const; // real length of rightside of the rule

    bool is_final() const;
};

bool operator<(const situation &a, const situation &b);

bool operator==(const situation &a, const situation &b);

// operators needed for comparison in sets