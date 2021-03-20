//-----------------------------------------------------------------------------
/// color.h: definition of the COLOR class
//-----------------------------------------------------------------------------

#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <iostream>

class COLOR
{
    public:
        COLOR() : r(0.0), g(0.0), b(0.0) {}
        COLOR(double rgb) : r(rgb), g(rgb), b(rgb) {}
        COLOR(double rr, double gg, double bb) :
        r(rr), g(gg), b(bb) {}
        virtual ~COLOR() {}

        COLOR operator * (const double &f) const
        { return COLOR(f * r, f * g, f * b); }
        COLOR operator / (const double& f) const
        { 
          if (f != 0.0) {
            return COLOR(r / f, g / f, b / f);
          }
          else {
            std::cout << "Error: dividing color by 0.0" << std::endl;
            return COLOR(1.0, 0.0, 1.0);
          }
        }
        COLOR operator + (const COLOR &c) const
        { return COLOR(r + c.r, g + c.g, b + c.b); }
        COLOR operator * (const COLOR &c) const
        { return COLOR(r * c.r, g * c.g, b * c.b); }
        COLOR& operator *= (const COLOR &c)
        { r *= c.r; g *= c.g; b *= c.b; return *this; }
        COLOR& operator += (const COLOR &c)
        { r += c.r; g += c.g; b += c.b; return *this; }
        COLOR& operator *= (const double &f)
        { r *= f; g *= f; b *= f; return *this; }
        COLOR& operator /= (const double& f)
        {
          if (f != 0.0) {
            r /= f; g /= f; b /= f; return *this;
          }
          else {
            std::cout << "Error: dividing color by 0.0" << std::endl;
            return COLOR(1.0, 0.0, 1.0);
          }
        }

        double r, g, b;
};

#endif // COLOR_H_INCLUDED
