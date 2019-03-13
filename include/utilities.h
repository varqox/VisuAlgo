#pragma once

#include <string>

namespace valgo {
template<class T>
constexpr inline auto string_length(const T& x) noexcept -> decltype(x.size());

template<class T>
constexpr inline size_t string_length(T* x) noexcept;

constexpr inline size_t string_length(char) noexcept;

template<class... Args>
std::string& back_insert(std::string& str, Args&&... args);

template<class... Args>
std::string concat(Args&&... args);

}

// The implementation of a non-specialized template must be visible to a translation unit that uses it.
// Do not add src/utilities.cc to Makefile
#include "../src/utilities.cc"