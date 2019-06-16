#include "../include/block.h"
#include "../include/latex.h"

#include <gtest/gtest.h>

using namespace valgo;

TEST(Block, clone) {
	// LaTeX backend
	EXPECT_EQ(Block("My block title").clone()->draw_as_latex(),
	          "\\begin{colorblock}{0000FF}{FFFFFF}{My block title}\n\\end{colorblock}");

	{
		Block block("lorem ipsum");
		EXPECT_EQ(block.clone()->draw_as_latex(), "\\begin{colorblock}{0000FF}{FFFFFF}{lorem ipsum}\n"
		                                          "\\end{colorblock}");

		block.add_elem(Latex("$a^2 + b^2 + c^2 = d^2$ - easy equation"));
		EXPECT_EQ(block.clone()->draw_as_latex(), "\\begin{colorblock}{0000FF}{FFFFFF}{lorem ipsum}\n"
		                                          "$a^2 + b^2 + c^2 = d^2$ - easy equation\n"
		                                          "\\end{colorblock}");

		block.add_elem(Latex("\\begin{itemize}\n\\item aaa\n\\item bbb\n\\end{itemize}"));
		EXPECT_EQ(block.clone()->draw_as_latex(), "\\begin{colorblock}{0000FF}{FFFFFF}{lorem ipsum}\n"
		                                          "$a^2 + b^2 + c^2 = d^2$ - easy equation\n"
		                                          "\\begin{itemize}\n"
		                                          "\\item aaa\n"
		                                          "\\item bbb\n"
		                                          "\\end{itemize}\n\\end{colorblock}");

		block.set_color(Color::CYAN);
		EXPECT_EQ(block.clone()->draw_as_latex(), "\\begin{colorblock}{00FFFF}{000000}{lorem ipsum}\n"
		                                          "$a^2 + b^2 + c^2 = d^2$ - easy equation\n"
		                                          "\\begin{itemize}\n"
		                                          "\\item aaa\n"
		                                          "\\item bbb\n"
		                                          "\\end{itemize}\n"
		                                          "\\end{colorblock}");
	}

	{
		Block block("lorem ipsum", Color::MAGENTA);
		EXPECT_EQ(block.clone()->draw_as_latex(), "\\begin{colorblock}{FF00FF}{FFFFFF}{lorem ipsum}\n"
		                                          "\\end{colorblock}");

		block.set_title("abc efg");
		EXPECT_EQ(block.clone()->draw_as_latex(), "\\begin{colorblock}{FF00FF}{FFFFFF}{abc efg}\n"
		                                          "\\end{colorblock}");
	}

	{
		Block block("lorem ipsum", Color::MAGENTA, Latex("$a^2 + b^2 + c^2 = d^2$ - easy equation"));
		EXPECT_EQ(block.clone()->draw_as_latex(), "\\begin{colorblock}{FF00FF}{FFFFFF}{lorem ipsum}\n"
		                                          "$a^2 + b^2 + c^2 = d^2$ - easy equation\n"
		                                          "\\end{colorblock}");
	}

	// HTML backend
	EXPECT_THROW(Block("My block title").clone()->draw_as_html(), NotImplemented);

	{
		Block block("lorem ipsum");
		EXPECT_THROW(block.clone()->draw_as_html(), NotImplemented);
		block.add_elem(Latex("$a^2 + b^2 + c^2 = d^2$ - easy equation"));
		EXPECT_THROW(block.clone()->draw_as_html(), NotImplemented);
		block.add_elem(Latex("\\begin{itemize}\n\\item aaa\n\\item bbb\n\\end{itemize}"));
		EXPECT_THROW(block.clone()->draw_as_html(), NotImplemented);
		block.set_color(Color::CYAN);
		EXPECT_THROW(block.clone()->draw_as_html(), NotImplemented);
	}

	{
		Block block("lorem ipsum", Color::MAGENTA);
		EXPECT_THROW(block.clone()->draw_as_html(), NotImplemented);
		block.set_title("abc efg");
		EXPECT_THROW(block.clone()->draw_as_html(), NotImplemented);
	}

	{
		Block block("lorem ipsum", Color::MAGENTA, Latex("$a^2 + b^2 + c^2 = d^2$ - easy equation"));
		EXPECT_THROW(block.clone()->draw_as_html(), NotImplemented);
	}
}

TEST(Block, draw_as_latex) {
	EXPECT_EQ(Block("My block title").draw_as_latex(),
	          "\\begin{colorblock}{0000FF}{FFFFFF}{My block title}\n\\end{colorblock}");

	{
		Block block("lorem ipsum");
		EXPECT_EQ(block.draw_as_latex(), "\\begin{colorblock}{0000FF}{FFFFFF}{lorem ipsum}\n"
		                                 "\\end{colorblock}");

		block.add_elem(Latex("$a^2 + b^2 + c^2 = d^2$ - easy equation"));
		EXPECT_EQ(block.draw_as_latex(), "\\begin{colorblock}{0000FF}{FFFFFF}{lorem ipsum}\n"
		                                 "$a^2 + b^2 + c^2 = d^2$ - easy equation\n"
		                                 "\\end{colorblock}");

		block.add_elem(Latex("\\begin{itemize}\n\\item aaa\n\\item bbb\n\\end{itemize}"));
		EXPECT_EQ(block.draw_as_latex(), "\\begin{colorblock}{0000FF}{FFFFFF}{lorem ipsum}\n"
		                                 "$a^2 + b^2 + c^2 = d^2$ - easy equation\n"
		                                 "\\begin{itemize}\n"
		                                 "\\item aaa\n"
		                                 "\\item bbb\n"
		                                 "\\end{itemize}\n\\end{colorblock}");

		block.set_color(Color::CYAN);
		EXPECT_EQ(block.draw_as_latex(), "\\begin{colorblock}{00FFFF}{000000}{lorem ipsum}\n"
		                                 "$a^2 + b^2 + c^2 = d^2$ - easy equation\n"
		                                 "\\begin{itemize}\n"
		                                 "\\item aaa\n"
		                                 "\\item bbb\n"
		                                 "\\end{itemize}\n"
		                                 "\\end{colorblock}");
	}

	{
		Block block("lorem ipsum", Color::MAGENTA);
		EXPECT_EQ(block.draw_as_latex(), "\\begin{colorblock}{FF00FF}{FFFFFF}{lorem ipsum}\n"
		                                 "\\end{colorblock}");

		block.set_title("abc efg");
		EXPECT_EQ(block.draw_as_latex(), "\\begin{colorblock}{FF00FF}{FFFFFF}{abc efg}\n"
		                                 "\\end{colorblock}");
	}

	{
		Block block("lorem ipsum", Color::MAGENTA, Latex("$a^2 + b^2 + c^2 = d^2$ - easy equation"));
		EXPECT_EQ(block.draw_as_latex(), "\\begin{colorblock}{FF00FF}{FFFFFF}{lorem ipsum}\n"
		                                 "$a^2 + b^2 + c^2 = d^2$ - easy equation\n"
		                                 "\\end{colorblock}");
	}
}

TEST(Block, draw_as_html) {
	EXPECT_THROW(Block("My block title").draw_as_html(), NotImplemented);

	{
		Block block("lorem ipsum");
		EXPECT_THROW(block.draw_as_html(), NotImplemented);
		block.add_elem(Latex("$a^2 + b^2 + c^2 = d^2$ - easy equation"));
		EXPECT_THROW(block.draw_as_html(), NotImplemented);
		block.add_elem(Latex("\\begin{itemize}\n\\item aaa\n\\item bbb\n\\end{itemize}"));
		EXPECT_THROW(block.draw_as_html(), NotImplemented);
		block.set_color(Color::CYAN);
		EXPECT_THROW(block.draw_as_html(), NotImplemented);
	}

	{
		Block block("lorem ipsum", Color::MAGENTA);
		EXPECT_THROW(block.draw_as_html(), NotImplemented);
		block.set_title("abc efg");
		EXPECT_THROW(block.draw_as_html(), NotImplemented);
	}

	{
		Block block("lorem ipsum", Color::MAGENTA, Latex("$a^2 + b^2 + c^2 = d^2$ - easy equation"));
		EXPECT_THROW(block.draw_as_html(), NotImplemented);
	}
}
