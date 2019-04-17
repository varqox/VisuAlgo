#include "../include/block.h"
#include "../include/itemize.h"
#include "../include/latex.h"
#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/source_code.h"
#include "../include/array_1d.h"
#include "../include/variable.h"
#include "../include/array_2d.h"
#include "../include/undirected_graph.h"
#include "../include/image.h"
#include "../include/image_set.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace valgo;

LatexPresentation pres("Visualization of images", "Images");
SlideBuilder sb;

int main () {
	Image im("./sample_images/" ,"kon2.jpg");
	Image im2("./sample_images/" ,"kon2.jpg");
	Image im3("./sample_images/" ,"kon2.jpg");
	Image im4("./sample_images/" ,"kon2.jpg");
	im.set_height(3);
	im.set_width(3);
	im2.set_height(3);
	im2.set_width(3);
	im3.set_height(3);
	im3.set_width(3);
	im4.set_height(3);
	im4.set_width(3);
	im.set_angle(0);
	im2.set_angle(90);
	im3.set_angle(180);
	im4.set_angle(270);
	im.set_top_shift(-3);
	im2.set_top_shift(0);
	im3.set_top_shift(2);
	im4.set_top_shift(0);
	im.set_right_shift(0);
	im2.set_right_shift(4);
	im3.set_right_shift(0);
	im4.set_right_shift(-4);
	Image im5("./sample_images/" ,"konik.jpeg");
	im5.set_width(2);
	im5.set_height(2);
	im5.set_top_shift(-0.5);

	ImageSet imset;

	imset.add_image(im3);
	imset.add_image(im5);
	imset.add_image(im);
	imset.add_image(im2);
	imset.add_image(im4);
	sb.add_elem(imset);
	pres.add_slide(sb.build().set_title("Images"));

	sb.remove_all_elements();

	pres.author("Dream team");
	pres.date("12.03.2019");
	pres.institute("MIMUW");
	cout << pres.to_str() << endl;
	return 0;
}