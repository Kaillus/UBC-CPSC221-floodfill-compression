#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    this->fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    return HSLAPixel(p.c.color.h, p.c.color.s, p.c.color.l * pow((fadeFactor), (sqrt(pow(p.x - p.c.x, 2) + pow(p.y - p.c.y, 2)))), p.c.color.a);

}
