#include "../include/latex.h"

#include <gtest/gtest.h>

using namespace valgo;

TEST(Latex, clone) {
	// LaTeX backend
	EXPECT_EQ(Latex().clone()->draw_as_latex(), "");

	{
		Latex latex("lorem ipsum");
		EXPECT_EQ(latex.clone()->draw_as_latex(), "lorem ipsum");
		latex.set("foo bar");
		EXPECT_EQ(latex.clone()->draw_as_latex(), "foo bar");
	}

	{
		Latex latex("$e=mc^2$");
		EXPECT_EQ(latex.clone()->draw_as_latex(), "$e=mc^2$");
		latex.set("\\newline");
		EXPECT_EQ(latex.clone()->draw_as_latex(), "\\newline");
	}

	// HTML backend
	EXPECT_THROW(Latex().clone()->draw_as_html(), NotImplemented);

	{
		Latex latex("lorem ipsum");
		EXPECT_THROW(latex.clone()->draw_as_html(), NotImplemented);
		latex.set("foo bar");
		EXPECT_THROW(latex.clone()->draw_as_html(), NotImplemented);
	}
}

TEST(Latex, set) {
	{
		Latex latex("lorem ipsum");
		latex.set("foo bar"); // Setting on value-initialized latex
		EXPECT_EQ(latex.draw_as_latex(), "foo bar");
	}

	{
		Latex latex;
		latex.set("$e=mc^2$"); // Setting on empty-initialized Latex
		EXPECT_EQ(latex.draw_as_latex(), "$e=mc^2$");
		latex.set("\\newline");
		EXPECT_EQ(latex.draw_as_latex(), "\\newline");
	}
}

TEST(Latex, draw_as_latex) {
	EXPECT_EQ(Latex().draw_as_latex(), "");

	{
		Latex latex("lorem ipsum");
		EXPECT_EQ(latex.draw_as_latex(), "lorem ipsum");
		latex.set("foo bar");
		EXPECT_EQ(latex.draw_as_latex(), "foo bar");
	}

	{
		Latex latex("$e=mc^2$");
		EXPECT_EQ(latex.draw_as_latex(), "$e=mc^2$");
		latex.set("\\newline");
		EXPECT_EQ(latex.draw_as_latex(), "\\newline");
	}
}

TEST(Latex, draw_as_html) {
	EXPECT_THROW(Latex().draw_as_html(), NotImplemented);

	Latex latex("lorem ipsum");
	EXPECT_THROW(latex.draw_as_html(), NotImplemented);
	latex.set("foo bar");
	EXPECT_THROW(latex.draw_as_html(), NotImplemented);
}
