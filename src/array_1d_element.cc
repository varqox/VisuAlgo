#include "../include/array_1d_element.h"

namespace valgo {
template<class  T>
void Array1DElement<T>::set(std::vector<T> vec) noexcept {
    vec_ = std::move(vec);
}

template<class T>
void Array1DElement<T>::resize(size_t n) {
    vec_.resize(n);
}

template<class T>
void Array1DElement<T>::set_elem(size_t n, T val) {
    vec_[n] = std::move(val);
}

}   // namespace valgo
