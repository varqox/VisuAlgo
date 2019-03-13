#include "../include/array_2d_element.h"

namespace valgo {

template <class T>
void Array2DElement<T>::resize(size_t n, size_t m) {
    vec_.resize(n * m);
}

template <class T>
void Array2DElement<T>::set_elem(size_t i, size_t j, T val) {
    vec_[i * m_ + j] = std::move(val);
}

}   // namespace valgo
