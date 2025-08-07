#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  // 所有指向空字符的迭代器
  auto spaces = find_all(source.begin(), source.end(), [](char c){
    return std::isspace(static_cast<unsigned char>(c));
  }); 

  if (spaces.size() < 2) {
    return {};
  }

  // 在连续空格字符之间生成标记
  Corpus tokens;
  std::transform(
    spaces.begin(), spaces.end() - 1,
    spaces.begin() + 1,
    std::inserter(tokens, tokens.end()),
    [&source](auto& it1, auto& it2) {
      return Token(source, it1, it2);
    }
  );

  // 去除空标记 会有连续的空白字符的情况
  std::erase_if(tokens, [](const Token& token) {
    return token.content.empty();
  });

  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;

  std::set<Misspelling> result;

  for (const Token& token : source) {
    if (dictionary.contains(token.content)) continue;

    const std::string& word = token.content;

    auto suggestion_views = dictionary
    | rv::filter([&word](const std::string& candidate) {
      return levenshtein(word, candidate) == 1;
    });

    std::set<std::string> suggestions(suggestion_views.begin(), suggestion_views.end());
    
    if (!suggestions.empty()) {
      result.insert(Misspelling{token, suggestions});
    }
  }
  return result;
};

/* Helper methods */

#include "utils.cpp"