#pragma once

#include <string>

namespace valgo {
template<class T>
constexpr inline auto string_length(const T& x) noexcept -> decltype(x.size()) {
	return x.size();
}

template<class T>
constexpr inline size_t string_length(T* x) noexcept {
	return std::char_traits<T>::length(x);
}

constexpr inline size_t string_length(char) noexcept { return 1; }

template<class... Args>
inline std::string& back_insert(std::string& str, Args&&... args);

template<class... Args>
inline std::string concat(Args&&... args);

/****************** Implementation ******************/

template<class... Args>
inline std::string& back_insert(std::string& str, Args&&... args) {
    size_t total_length = str.size();
    ((total_length += string_length(args)), ...);

    // Allocate more space (reserve is inefficient)
    size_t old_size = str.size();
    str.resize(total_length);
    str.resize(old_size);

    ((str += std::forward<Args>(args)), ...);
    return str;
}

template<class... Args>
inline std::string concat(Args&&... args) {
    std::string str;
    back_insert(str, std::forward<Args>(args)...);
    return str;
}

} // namespace valgo
