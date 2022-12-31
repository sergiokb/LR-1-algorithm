#include <gtest/gtest.h>
#include "../src/solution.h"

TEST(MyTests, Grammar_0) {
    std::vector<std::string> words;
    std::vector<std::string> ans;
    solution("tests/examples/grammar_0.txt",
             "tests/examples/words_0.txt",words, ans);
    EXPECT_EQ(ans[0], "YES 32314231");
    EXPECT_EQ(ans[1], "NO");
}

TEST(MyTests, Grammar_1) {
    std::vector<std::string> words;
    std::vector<std::string> ans;
    solution("tests/examples/grammar_1.txt",
             "tests/examples/words_1.txt",words, ans);
    EXPECT_EQ(ans[0], "NO");
    EXPECT_EQ(ans[1], "YES 22211");
}

TEST(MyTests, Grammar_2) {
    std::vector<std::string> words;
    std::vector<std::string> ans;
    solution("tests/examples/grammar_2.txt",
             "tests/examples/words_2.txt",words, ans);
    EXPECT_EQ(ans[0], "YES 43321");
    EXPECT_EQ(ans[1], "NO");
}

TEST(MyTests, Grammar_3) {
    std::vector<std::string> words;
    std::vector<std::string> ans;
    solution("tests/examples/grammar_3.txt",
             "tests/examples/words_3.txt",words, ans);
    EXPECT_EQ(ans[0], "YES 32232221");
    EXPECT_EQ(ans[1], "NO");
}

TEST(TestingFIRST, SpecialCase) {
    std::set<char> firsts = testing_first("tests/first_testing/grammar.txt",
                                          {1, 0, 1, 'a'});
    ASSERT_EQ(firsts.size(), 1);
    EXPECT_EQ(*firsts.begin(), 'a');
}

// I give an example of situation [S -> a.TT,a] where there is a rule T -> $
// Previously, find_possible_words would return '$', which is wrong,
// and now it returns 'a', which is correct.




