#include "../include/image.h"
#include "../include/image_set.h"

#include <gtest/gtest.h>
using namespace valgo;

TEST(Image, draw_as_latex) {
	Image im("./sample_images/", "kon2.jpg");
	EXPECT_EQ(im.draw_as_latex(), "\\graphicspath{ {./sample_images/} }\n\\node [xshift=0cm] "
	                              "[yshift=0cm]{\\includegraphics[height=0cm, width=0cm, angle = 0]{kon2.jpg}};\n");
}

TEST(Image, draw_as_html) {
	Image im("./sample_images/", "kon2.jpg");
	EXPECT_THROW(im.draw_as_html(), NotImplemented);
}

TEST(Image, set_width) {
	Image im("./sample_images/", "kon2.jpg");
	im.set_width(2.2);
	EXPECT_EQ(im.draw_as_latex(), "\\graphicspath{ {./sample_images/} }\n\\node [xshift=0cm] "
	                              "[yshift=0cm]{\\includegraphics[height=0cm, width=2.2cm, angle = 0]{kon2.jpg}};\n");
}

TEST(Image, set_height) {
	Image im("./sample_images/", "kon2.jpg");
	im.set_height(-1.4);
	EXPECT_EQ(im.draw_as_latex(), "\\graphicspath{ {./sample_images/} }\n\\node [xshift=0cm] "
	                              "[yshift=0cm]{\\includegraphics[height=-1.4cm, width=0cm, angle = 0]{kon2.jpg}};\n");
}

TEST(Image, set_right_shift) {
	Image im("./sample_images/", "kon2.jpg");
	im.set_right_shift(0.55);
	EXPECT_EQ(im.draw_as_latex(), "\\graphicspath{ {./sample_images/} }\n\\node [xshift=0.55cm] "
	                              "[yshift=0cm]{\\includegraphics[height=0cm, width=0cm, angle = 0]{kon2.jpg}};\n");
}

TEST(Image, set_top_shift) {
	Image im("./sample_images/", "kon2.jpg");
	im.set_top_shift(-3.2);
	EXPECT_EQ(im.draw_as_latex(), "\\graphicspath{ {./sample_images/} }\n\\node [xshift=0cm] "
	                              "[yshift=-3.2cm]{\\includegraphics[height=0cm, width=0cm, angle = 0]{kon2.jpg}};\n");
}

TEST(Image, set_angle) {
	Image im("./sample_images/", "kon2.jpg");
	im.set_angle(45);
	EXPECT_EQ(im.draw_as_latex(), "\\graphicspath{ {./sample_images/} }\n\\node [xshift=0cm] "
	                              "[yshift=0cm]{\\includegraphics[height=0cm, width=0cm, angle = 45]{kon2.jpg}};\n");
}

TEST(ImageSet, draw_as_latex) {
	ImageSet imset;
	EXPECT_EQ(imset.draw_as_latex(), "\\begin{center}\n\\begin{tikzpicture}[remember picture,overlay,shift={(current "
	                                 "page.center)}]\n\\end{tikzpicture}\n\\end{center}\n");
}

TEST(ImageSet, add_image) {
	ImageSet imset;
	Image im("./sample_images/", "kon2.jpg");
	Image im2("./sample_images/", "kon2.jpg");

	im.set_angle(0);
	im.set_height(3);
	im.set_right_shift(0);
	im.set_top_shift(-3);
	im.set_width(3);

	im2.set_angle(90);
	im2.set_height(3);
	im2.set_right_shift(4);
	im2.set_top_shift(0);
	im2.set_width(3);

	imset.add_image(im);
	imset.add_image(im2);

	EXPECT_EQ(imset.draw_as_latex(),
	          "\\begin{center}\n\\begin{tikzpicture}[remember picture,overlay,shift={(current "
	          "page.center)}]\n\\graphicspath{ {./sample_images/} }\n\\node [xshift=0cm] "
	          "[yshift=-3cm]{\\includegraphics[height=3cm, width=3cm, angle = 0]{kon2.jpg}};\n\\graphicspath{ "
	          "{./sample_images/} }\n\\node [xshift=4cm] [yshift=0cm]{\\includegraphics[height=3cm, width=3cm, angle "
	          "= 90]{kon2.jpg}};\n\\end{tikzpicture}\n\\end{center}\n");
}