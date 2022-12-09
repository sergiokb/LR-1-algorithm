#include <gtest/gtest.h>
#include "../src/solution.h"

TEST(MyTests, SimpleRegex_1) {
    std::vector<std::string> words;
    std::vector<std::string> ans;
    solution("tests/examples/grammar_0.txt",
             "tests/examples/words_0.txt",words, ans);
    EXPECT_EQ(ans[0], "YES 32314231");
}






