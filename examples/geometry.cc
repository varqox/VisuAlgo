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

    geo.add(p).add(p2);
    geo.add(p3);
    geo.add(l);

    pres.add_slide(sb.build().set_title("title xd"));

    geo.erase(p3);
    geo.set_coord_system(-6, 6, -6, 6);
    p2.set_label("punkcik");
    l.set_label("prosta");

    Rectangle r(-2, -2, 2, 2, "prostokącik");
    geo.add(r);

    Circle c(-2, 2, 2, "Kółeczko");
    geo.add(c);

    pres.add_slide(sb.build().set_title("lel xD"));

    cout << pres.to_str() << endl;
    return 0;
}