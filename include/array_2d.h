#pragma once

#include "slide_element.h"

#include <sstream>
#include <vector>

namespace valgo {

template<class T>
class Array2D : public SlideElement {
private:
	size_t n_, m_;
	std::vector<T> vec_; // n_ x m_

public:
	Array2D() = default;

	virtual std::unique_ptr<SlideElement> clone() const override {
		 return std::make_unique<Array2D>(*this);
	}

	void resize(size_t n, size_t m) {
		vec_.resize(n * m);
		n_ = n;
		m_ = m;
	}

	void set_elem(size_t i, size_t j, T val) {
		vec_[i * n_ + j] = std::move(val);
	}

	virtual LatexCode draw_as_latex() const override {
		std::stringstream ret;
		ret << "\\begin{table}[h!]\n \\begin{tabular}{|";

		for (size_t i = 0; i < m_; i++)
            ret << "c|";
        ret << "}\n  \\hline\n  ";

        for (size_t i = 0; i < n_; i++) {
        	for (size_t j = 0; j < m_; j++) {
        		if (j < m_ - 1)  {
                	ret << " " << vec_[i * n_ + j] << " &";
            	}
            	else {
                	ret << " " << vec_[i * n_ + j] << "\\\\\n  \\hline\n";
            	}
        	}

        	if (i != n_ - 1)
        		ret << "  ";
        }

        ret << " \\end{tabular}\n \\end{table}\n";

        return ret.str();
	}

	virtual HTMLCode draw_as_html() const override {
        throw NotImplemented();
    }
};

} // namespace valgo
