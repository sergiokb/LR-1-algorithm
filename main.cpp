#include "src/solution.h"

int main() {
    std::vector<std::string> words;
    std::vector<std::string> ans;
    solution("grammar.txt",
         "words.txt", words, ans);
    for(size_t i = 0; i < ans.size(); ++i) {
        std::cout << words[i] << " - " << ans[i] << '\n';
    }
    return 0;
}
