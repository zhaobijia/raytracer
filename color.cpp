#include "pch.h"
#include "color.h"

Color::Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a):r(_r),g(_g),b(_b),a(_a)
{
	update_float_value();
}
Color::Color(float _r, float _g, float _b, float _a):fr(_r),fg(_g),fb(_b),fa(_a)
{
	update_uchar_value();
 }
Color::Color(const Color& c)
{
	r = c.r;
	g = c.g;
	b = c.b;
	a = c.a;
	update_float_value();
}
Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	a = 255;
	fr = 0;
	fg = 0;
	fb = 0;
	fa = 1.f;
}
Color::~Color(){}

void Color::update_float_value()
{
	fr = static_cast<float>(r / 255.999f);
	fg = static_cast<float>(g / 255.999f);
	fb = static_cast<float>(b / 255.999f);
	fa = static_cast<float>(a / 255.999f);
}

void Color::update_uchar_value()
{
	r = static_cast<unsigned char>(255.999 * fr);
	g = static_cast<unsigned char>(255.999 * fg);
	b = static_cast<unsigned char>(255.999 * fb);
	a = static_cast<unsigned char>(255.999 * fa);

}

Color Color::operator *(float t)
{
	if (t > 0.f && t < 1.f)
	{
		fr = fr * t;
		fg = fg * t;
		fb = fb * t;
		//fa = fa * t;
		update_uchar_value();
	}
	return *this;
}

Color Color::operator *(const Color& c)
{
	fr = fr * c.fr;
	fg = fg * c.fg;
	fb = fb * c.fb;
	//fa = fb * c.fa;
	update_uchar_value();
	return *this;
}


int write_color_to_image(unsigned char* image, int index, Color color)
{
	image[index++] = color.r;
	image[index++] = color.g;
	image[index++] = color.b;
	image[index++] = color.a;

	return index;
}