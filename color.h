#ifndef __COLOR_H__
#define __COLOR_H__


class Color
{

public:
	Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
	Color(float dr, float dg, float db, float da);
	Color(const Color& c);
	Color();
	~Color();

	void update_float_value();
	void update_uchar_value();
	
	Color operator *(float t);
	Color operator *(const Color& c);
public:
	unsigned char r, g, b, a;
	float fr, fg, fb, fa;

};

int write_color_to_image(unsigned char* image, int index, Color color);

#endif //__COLOR_H__