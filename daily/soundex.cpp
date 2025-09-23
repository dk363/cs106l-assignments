//
// Created by dk on 2025/9/23.
//
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <ranges>

#include <iostream>

static char soundexEncode(char c) {
    static const std::map<char, char> encoding = {
        {'A', '0'}, {'E', '0'}, {'I', '0'}, {'O', '0'}, {'U', '0'}, {'H', '0'}, {'W', '0'}, {'Y', '0'},
        {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
        {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
        {'D', '3'}, {'T', '3'},
        {'L', '4'},
        {'M', '5'}, {'N', '5'},
        {'R', '6'}
    };
    return encoding.at(std::toupper(c));
}

static bool notZero(char c) {
    return c != '0';
}


std::string soundex(const std::string& s) {
    // ranges 返回的是一个 iterator
    std::string letters;
    std::ranges::copy_if(s, std::back_inserter(letters), ::isalpha);

    char first_letter = letters[0];

    std::string unique;
    std::ranges::unique_copy(letters, std::back_inserter(unique));

    unique[0] = std::toupper(first_letter);

    std::string no_zeros;
    std::ranges::copy_if(unique, std::back_inserter(no_zeros), notZero);

    no_zeros += "0000";
    return no_zeros.substr(0, 4);
}

std::string soundexRanges(const std::string& s) {
    namespace rv = std::ranges::views;

    auto first = *std::ranges::find_if(s, ::isalpha);
    auto v = s | rv::filter(::isalpha) | rv::transform(soundexEncode);

    std::string encode;
    std::ranges::unique_copy(v, std::back_inserter(encode));
    encode[0] = toupper(first);

    return encode
            | rv::filter(notZero)
            | rv::concat("0000")
            | rv::take(4)
            | std::ranges::to<std::string<>();
}
