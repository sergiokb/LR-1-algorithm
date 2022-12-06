#include "grammar.h"

struct situation {
    int left;
    int right_index;
    int dot_position;
    char word;

    int after_dot(Grammar &gr) const;

    int rightside_length(Grammar &gr) const;

    bool is_final() const;
};

bool operator<(const situation &a, const situation &b);

bool operator==(const situation &a, const situation &b);

