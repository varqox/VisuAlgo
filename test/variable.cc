#include "../include/variable.h"

#include <gtest/gtest.h>

using namespace valgo;

TEST(Variable, set) {
	{
		Variable<int> variable("magic");
		variable.set(42);
		EXPECT_EQ(variable.draw_as_latex(), "magic = 42\\\\\n");
		variable.set(43);
		EXPECT_EQ(variable.draw_as_latex(), "magic = 43\\\\\n");
	}

	{
		Variable<double> variable("pi");
		variable.set(3.14159);
		EXPECT_EQ(variable.draw_as_latex(), "pi = 3.14159\\\\\n");
		variable.set(2.781);
		EXPECT_EQ(variable.draw_as_latex(), "pi = 2.781\\\\\n");
	}

	{
		Variable<std::string> variable("thue");
		variable.set("abba");
		EXPECT_EQ(variable.draw_as_latex(), "thue = abba\\\\\n");
		variable.set("j_98g:Gg)d");
		EXPECT_EQ(variable.draw_as_latex(), "thue = j_98g:Gg)d\\\\\n");
	}

	{
		Variable<double> variable("pi");
		variable.set(3.14159);
		EXPECT_THROW(variable.draw_as_html(), NotImplemented);
		variable.set(2.781);
		EXPECT_THROW(variable.draw_as_html(), NotImplemented);
	}
}

TEST(Variable, setAndClone) {
	{
		Variable<int> variable("magic");
		variable.set(42);
		EXPECT_EQ(variable.clone()->draw_as_latex(), "magic = 42\\\\\n");
		variable.set(43);
		EXPECT_EQ(variable.clone()->draw_as_latex(), "magic = 43\\\\\n");
	}

	{
		Variable<double> variable("pi");
		variable.set(3.14159);
		EXPECT_EQ(variable.clone()->draw_as_latex(), "pi = 3.14159\\\\\n");
		variable.set(2.781);
		EXPECT_EQ(variable.clone()->draw_as_latex(), "pi = 2.781\\\\\n");
	}

	{
		Variable<std::string> variable("thue");
		variable.set("abba");
		EXPECT_EQ(variable.clone()->draw_as_latex(), "thue = abba\\\\\n");
		variable.set("j_98g:Gg)d");
		EXPECT_EQ(variable.clone()->draw_as_latex(), "thue = j_98g:Gg)d\\\\\n");
	}

	{
		Variable<double> variable("pi");
		variable.set(3.14159);
		EXPECT_THROW(variable.clone()->draw_as_html(), NotImplemented);
		variable.set(2.781);
		EXPECT_THROW(variable.clone()->draw_as_html(), NotImplemented);
	}
}
