#include "../include/latex_presentation.h"
#include "../include/slide_builder.h"
#include "../include/geometry.h"

#include <iostream>

using namespace valgo;
using namespace std;

LatexPresentation pres("Visualization of Geometry", "Euclid");
SlideBuilder sb;
Geometry geo;

int main() {
    sb.add_elem(geo);
    
    Point p(2, 4);
    Point p2(3, 3);
    Point p3(4, 2);

    Line l(1, 1, 5, 5);

    geo.add_elem(p);
    geo.add_elem(p2);
    geo.add_elem(p3);
    geo.add_elem(l);

    pres.add_slide(sb.build().set_title("title xd"));
    cout << pres.to_str() << endl;
    return 0;
}