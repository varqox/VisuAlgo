#pragma once

#include "slide_element.h"

#include <vector>

namespace valgo {

template<class T>
class Array1DElement : public SlideElement {
private:
    std::vector<T> vec_;

public:
    Array1DElement() = default;

    virtual std::unique_ptr<SlideElement> clone() const override {
        return std::make_unique<Array1DElement>(*this);
    }

    void set(std::vector<T> vec) noexcept { vec_ = std::move(vec); }

    void resize(size_t n) { vec_.resize(n); }

    void set_elem(size_t n, T val) { vec_[n] = std::move(val); }

    virtual LatexCode draw_as_latex() const override {
        std::string ret = "\\begin{table}[h!]\n \\begin{tabular}{|";
        
        for (size_t i = 0; i < vec_.size(); i++)
            ret += "c|";
        ret += "}\n  \\hline\n  ";
        
        for (size_t i = 0; i < vec_.size(); i++) {
            if (i < vec_.size() - 1)  {
                ret += " " + std::to_string(vec_[i]) + " &";
            }
            else {
                ret += " " + std::to_string(vec_[i]) + "\\\\\n  \\hline\n";
            }
        }

        ret += " \\end{tabular}\n \\end{table}\n";

        return ret;
    }

    virtual HTMLCode draw_as_html() const override {
        throw NotImplemented();
    }
};

} // namespace valgo
