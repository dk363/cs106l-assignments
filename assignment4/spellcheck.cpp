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

  // 标记 space
  // auto spaces = find_all(source.begin(), source.end(), 
  //   [](char c) { // 这里如果写 std::isspace会产生重载/模板二义性的问题
  //     // 在<cctype> <string> 中有两个同名函数 这里会报错
  //     return std::isspace(static_cast<unsigned char>(c));
  //   });
  // 第二种写法
  auto spaces = find_all(source.begin(), source.end(), ::isspace);
  Corpus tokens; // std::set<Token>
  std::transform(
    // 对两个等长的序列中的对应元素应用一个二元操作
    spaces.begin(), spaces.end() - 1, // 这一行提供了 iterator begin()
    spaces.begin() + 1, // 这一行提供了 end()
    std::inserter(tokens, tokens.end()), // output
    [&source](auto& it1, auto& it2) { // 构造 Token
      return Token(source, it1, it2);
    }
  );

  // 去除空标记 因为字符串中可能有多个连续的空格
  std::erase_if(tokens, [](const Token& token) {
    return token.content.empty();
  });

  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;

  // 跳过正确的单词
  auto view = source 
  | rv::filter([&dictionary](const auto& token) {
    // 如果 == 那就说明没有
    return dictionary.find(token.content) == dictionary.end();
    });
  
  // 因为 views 是懒惰计算的 所以不会生成中间容器
  // 也就是说这里需要重新copy
  auto misspelling_views = view
  | rv::transform([&dictionary](const auto& token) {
    auto suggestion_views = dictionary
      | rv::filter([&token](const auto& candidate) {
        return levenshtein(token.content, candidate) == 1;
      });

      std::set<std::string> suggestions(suggestion_views.begin(), suggestion_views.end());
      return Misspelling{token, suggestions};
    })
  | rv::filter([](const auto& m) {
    return !m.suggestions.empty();
  });

  std::set<Misspelling> result;
  std::ranges::copy(misspelling_views, std::inserter(result, result.end()));

  return result;
};

/* Helper methods */

#include "utils.cpp"