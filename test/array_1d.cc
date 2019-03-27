#include "../include/array_1d.h"

#include <gtest/gtest.h>

using namespace valgo;

TEST (Array1D, draw_as_latex) {
	EXPECT_EQ(Array1D<int>().draw_as_latex(), "\\begin{table}[h!]\n \\begin{tabular}{|}\n  \\hline\n  \\hline\n \\end{tabular}\n\\end{table}\n");
}

TEST (Array1D, draw_as_html) {
	EXPECT_THROW(Array1D<int>().draw_as_html(), NotImplemented);
}

TEST (Array1D, clone) {
	EXPECT_EQ(Array1D<int>().clone()->draw_as_latex(), "\\begin{table}[h!]\n \\begin{tabular}{|}\n  \\hline\n  \\hline\n \\end{tabular}\n\\end{table}\n");

	{	
		Array1D<int> arr("array");
		EXPECT_EQ(arr.clone()->draw_as_latex(), "\\begin{table}[h!]\n \\begin{tabular}{c|}\n  \\hhline{~|*{0}{-}}\n   array[i] &   \\hhline{~|*{0}{-}}\n   \\multicolumn{1}{c}{i} &  \\end{tabular}\n\\end{table}\n");
	}
}

TEST (Array1D, set) {
		Array1D<int> arr;
		std::vector<int> vec;
		vec.push_back(3);
		vec.push_back(5);
		vec.push_back(8);
		arr.set(vec);
		EXPECT_EQ(arr.clone()->draw_as_latex(),"\\begin{table}[h!]\n \\begin{tabular}{|c|c|c|}\n  \\hline\n3 & 5 & 8 \\\\\n  \\hline\n \\end{tabular}\n\\end{table}\n");

		Array1D<int> arr2("array");
		arr2.set(vec);

		EXPECT_EQ(arr2.clone()->draw_as_latex(), "\\begin{table}[h!]\n \\begin{tabular}{c|c|c|c|}\n  \\hhline{~|*{3}{-}}\n   array[i] & 3 & 5 & 8 \\\\\n  \\hhline{~|*{3}{-}}\n   \\multicolumn{1}{c}{i} & \\multicolumn{1}{c}{0} & \\multicolumn{1}{c}{1} & \\multicolumn{1}{c}{2} \n \\end{tabular}\n\\end{table}\n");
}

//set_color and set_range_color are speial cases of set_range_color
TEST (Array1D, set_range_color) {

	Array1D<int> arr("array");
	std::vector<int> vec;
	
	for (int i = 0; i < 10; i++)
		vec.push_back(2 * i + 1);

	arr.set(vec);
	arr.set_range_color(3, 6, Color::LIGHT_RED);

	EXPECT_EQ(arr.clone()->draw_as_latex(), "\\begin{table}[h!]\n \\begin{tabular}{c|c|c|c|c|c|c|c|c|c|c|}\n  \\hhline{~|*{10}{-}}\n   array[i] & 1 & 3 & 5 & \\cellcolor[HTML]{FF6961}7 & \\cellcolor[HTML]{FF6961}9 & \\cellcolor[HTML]{FF6961}11 & \\cellcolor[HTML]{FF6961}13 & 15 & 17 & 19 \\\\\n  \\hhline{~|*{10}{-}}\n   \\multicolumn{1}{c}{i} & \\multicolumn{1}{c}{0} & \\multicolumn{1}{c}{1} & \\multicolumn{1}{c}{2} & \\multicolumn{1}{c}{3} & \\multicolumn{1}{c}{4} & \\multicolumn{1}{c}{5} & \\multicolumn{1}{c}{6} & \\multicolumn{1}{c}{7} & \\multicolumn{1}{c}{8} & \\multicolumn{1}{c}{9} \n \\end{tabular}\n\\end{table}\n");
}

TEST (Array1D, resize) {
	Array1D<int> arr("array");
	std::vector<int> vec;
	
	for (int i = 0; i < 10; i++)
		vec.push_back(2 * i + 1);

	arr.set(vec);
	arr.resize(11);
	arr.set_elem(10, 666);
	EXPECT_EQ(arr.clone()->draw_as_latex(),"\\begin{table}[h!]\n \\begin{tabular}{c|c|c|c|c|c|c|c|c|c|c|c|}\n  \\hhline{~|*{11}{-}}\n   array[i] & 1 & 3 & 5 & 7 & 9 & 11 & 13 & 15 & 17 & 19 & 666 \\\\\n  \\hhline{~|*{11}{-}}\n   \\multicolumn{1}{c}{i} & \\multicolumn{1}{c}{0} & \\multicolumn{1}{c}{1} & \\multicolumn{1}{c}{2} & \\multicolumn{1}{c}{3} & \\multicolumn{1}{c}{4} & \\multicolumn{1}{c}{5} & \\multicolumn{1}{c}{6} & \\multicolumn{1}{c}{7} & \\multicolumn{1}{c}{8} & \\multicolumn{1}{c}{9} & \\multicolumn{1}{c}{10} \n \\end{tabular}\n\\end{table}\n");

}
