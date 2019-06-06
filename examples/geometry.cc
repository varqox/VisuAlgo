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
    p.set_color(Color::RED);
    p2.set_color(Color::GREEN);
    p3.set_color(Color::BLUE);

    geo.add(p).add(p2).add(p3);
    pres.add_slide(sb.build().set_title("Colorful points"));

    Line l(1, 1, 5, 5);
    Line l2(-3, 2, 3, -4);
    l.set_color(Color::MAGENTA);
    l.set_label("Magenta");
    l2.set_color(Color::CYAN);
    l2.set_label("Cyan");
    
    geo.add(l).add(l2);

    pres.add_slide(sb.build().set_title("Colorful points and lines"));
    
    geo.set_coord_system(-4, 6, -5, 6);
    
    p.set_label("(2, 4)");
    p2.set_label("(3, 3)");
    p3.set_label("(4, 2)");

    pres.add_slide(sb.build().set_title("Colorful points and lines with coordinate system"));


    geo.remove_all_elements();
    geo.set_coord_system(-5, 5, -5, 5);

    Rectangle r(-4, -2, 2, 2, "Rectangle");
    r.set_color(Color::RED);
    geo.add(r);

    Circle c(-2, -2.3, 2.5, "Circle");
    c.set_color(Color::GREEN);
    geo.add(c);

    Polygon pol;
    pol.add_vertex(3, -3).add_vertex(5, 4).add_vertex(3, 5).add_vertex(0, 3).add_vertex(1, 0);
    pol.set_color(Color::BLUE);
    pol.set_label("Pentagon");

    geo.add(pol);

    pres.add_slide(sb.build().set_title("Colorful polygons"));

    geo.remove_all_elements();
    geo.unset_coord_system();

    Vector v(0, 0, 2, 0);
    v.set_color(Color::RED);
    Vector v1(0, 0, 0, 2);
    v1.set_color(Color::GREEN);
    Vector v2(0, 0, -2, 0);
    v2.set_color(Color::BLUE);
    Vector v3(0, 0, 0, -2);
    v3.set_color(Color::YELLOW);

    Vector v4(0, 0, 1.41, 1.41);
    v4.set_color(Color::MAGENTA);
    Vector v5(0, 0, 1.41, -1.41);
    v5.set_color(Color::CYAN);
    Vector v6(0, 0, -1.41, 1.41);
    v6.set_color(Color::LIGHT_BROWN);
    Vector v7(0, 0, -1.41, -1.41);
    v7.set_color(Color::LIGHT_RED);

    geo.add(v).add(v1).add(v2).add(v3).add(v4).add(v5).add(v6).add(v7);

    pres.add_slide(sb.build().set_title("Colorful vectors"));



    cout << pres.to_str() << endl;
    return 0;
}