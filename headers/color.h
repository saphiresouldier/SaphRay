//-----------------------------------------------------------------------------
/// color.h: definition of the COLOR class
//-----------------------------------------------------------------------------

#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

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

        double r, g, b;
};

#endif // COLOR_H_INCLUDED
