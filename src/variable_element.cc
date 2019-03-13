#include "../include/variable_element.h"

namespace valgo {
template <class T>
void VariableElement<T>::set(T var) {
    var_ = std::move(var);
}

}   // namespace valgo
