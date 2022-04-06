#ifndef __MATHS_H__
#define __MATHS_H__
#include <math.h>
#include <iostream>
#include <assert.h>

# define M_PI           3.14159265358979323846  /* pi */

class Vector2
{
public:
	double x, y;
	Vector2() :x(0), y(0) {}
	Vector2(double _x, double _y) :x(_x), y(_y) {};
	~Vector2() {};
	double len() { return std::sqrt(x * x + y * y); }
	double dot(const Vector2& v) { return x * v.x + y * v.y; }
	Vector2 operator +(const Vector2& rhs) { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator -(const Vector2& rhs) { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator *(double t) { return Vector2(x * t, y * t); }
	Vector2 operator /(double t)
	{
		if (t == 0)
		{
			return Vector2(x, y);
		}
		return Vector2(x / t, y / t);
	}
	friend std::ostream& operator <<(std::ostream& out, const Vector2& v);

};
inline std::ostream& operator <<(std::ostream& out, const Vector2& v)
{
	out << "x: " << v.x << ", y: " << v.y;
	return out;
}



 class Vector3
{
private:
	double arr[3];
public:

	double x, y, z;

	Vector3() :x(0), y(0), z(0)
	{
		arr[0] = x;
		arr[1] = y;
		arr[2] = z;
	}
	Vector3(double _x, double _y, double _z) :x(_x), y(_y), z(_z)
	{
		arr[0] = x;
		arr[1] = y;
		arr[2] = z;
	}
	~Vector3() {}

	double* get_vector_arr()
	{ 
		arr[0] = x;
		arr[1] = y;
		arr[2] = z;
		return arr; 
	}
	double dot(const Vector3& v) { return x * v.x + y * v.y + z * v.z; }
	Vector3 cross(const Vector3& v) { return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	double len() { return std::sqrt(x * x + y * y + z * z); }

	Vector3 normalize()
	{
		*this = (*this) * (1/ this->len());
		return *this;
	}
	//Vector4 to_homogeneous()
	//{
	//	Vector4 h(x, y, z, 1);
	//	return h;
	//}

	Vector3 operator +(const Vector3& rhs) { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator -(const Vector3& rhs) { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator *(double t) { return Vector3(x * t, y * t, z * t); }
	Vector3 operator /(double t)
	{
		if (t == 0)
		{
			return Vector3(x, y, z);
		}
		return Vector3(x / t, y / t, z / t);
	}
	friend std::ostream& operator<< (std::ostream& out, const Vector3& v);

};
inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
	out << "x: " << v.x << ", y: " << v.y << ", z: " << v.z;
	return out;
}
class Vector4
{
public:
	double x, y, z, w;
	double arr[4];
	Vector4() :x(0.), y(0.), z(0.), w(0.) 
	{
		arr[0] = x;
		arr[1] = y;
		arr[2] = z;
		arr[3] = w;
	}
	Vector4(double _x, double _y, double _z, double _w) :x(_x), y(_y), z(_z), w(_w)
	{
		arr[0] = x;
		arr[1] = y;
		arr[2] = z;
		arr[3] = w;
	}
	Vector4(Vector3 vec3, double t)
	{
		x = vec3.x;
		y = vec3.y;
		z = vec3.z;
		w = t;
		arr[0] = x;
		arr[1] = y;
		arr[2] = z;
		arr[3] = w;
	}
	~Vector4() {}

	double dot(const Vector4& v) { return x * v.x + y * v.y + z * v.z + w * v.w; }
	double* get_vector_arr()
	{ 
		arr[0] = x;
		arr[1] = y;
		arr[2] = z;
		arr[3] = w;
		return arr;
	}


	Vector4 operator +(const Vector4& rhs) { return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
	Vector4 operator -(const Vector4& rhs) { return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
	Vector4 operator *(float t) { return Vector4(x * t, y * t, z * t, w * t); }
	friend std::ostream& operator<< (std::ostream& out, const Vector4& v);
};
 inline std::ostream& operator<<(std::ostream& out, const Vector4& v)
{
	out << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << ", w: " << v.w;
	return out;
}

//matrix
class Matrix3
{
public:
	double m[3][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

	Matrix3(void) {}
	Matrix3(Vector3 i, Vector3 j, Vector3 k)
	{
		m[0][0] = i.x;
		m[1][0] = i.y;
		m[2][0] = i.z;

		m[0][1] = j.x;
		m[1][1] = j.y;
		m[2][1] = j.z;

		m[0][2] = k.x;
		m[1][2] = k.y;
		m[2][2] = k.z;


	}

	~Matrix3() {}

	Vector3 operator *(Vector3& v)
	{
		double* v_arr = v.get_vector_arr();
		double rv[3] = { 0,0,0 }; //result vector

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				rv[i] += m[i][j] * v_arr[j];
			}
		}

		return Vector3(rv[0], rv[1], rv[2]);


	}

	Matrix3 transpose()
	{
		Matrix3 tp;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tp.m[i][j] = m[j][i];
			}
		}
		return tp;
	}
};


class Matrix4
{
public:
	double m[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };

	Matrix4(void) {}

	~Matrix4() {}

	void set_value(int row, int col, double val)
	{
		m[row][col] = val;
	}
	void set_identity()
	{
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = (double)1;
		m[0][1] = m[0][2] = m[0][3] = (double)0;
		m[1][0] = m[1][2] = m[1][3] = (double)0;
		m[2][0] = m[2][1] = m[2][3] = (double)0;
		m[3][0] = m[3][1] = m[3][2] = (double)0;
	}
	void set_zeros()
	{
		m[0][0] = m[0][1] = m[0][2] = m[0][3] = (double)0;
		m[1][0] = m[1][1] = m[1][2] = m[1][3] = (double)0;
		m[2][0] = m[2][1] = m[2][2] = m[2][3] = (double)0;
		m[3][0] = m[3][1] = m[3][2] = m[3][3] = (double)0;
	}
	Matrix4 transpose()
	{
		Matrix4 tp;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				tp.m[i][j] = m[j][i];
			}
		}
		return tp;
	}

	//matrix multiply matrix
	Matrix4 operator *(const Matrix4& rhs)
	{
		Matrix4 matrix;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				matrix.m[i][j] = m[i][0] * rhs.m[0][j] + m[i][1] * rhs.m[1][j] + m[i][2] * rhs.m[2][j] + m[i][3] * rhs.m[3][j];
			}
		}
		return matrix;
	}

	Vector3 mul(Vector3 v, double t)
	{
		double v_arr[4] = { v.x,v.y,v.z,t };
		double rv[4] = { 0,0,0,0 };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				rv[i] += m[i][j] * v_arr[j];
			}
		}

		if (t == 0)
		{
			return Vector3(rv[0], rv[1], rv[2]);
		}
		else {
			rv[3] = rv[3] == 0 ? 0.001 : rv[3];

			return Vector3(rv[0] / rv[3], rv[1] / rv[3], rv[2] / rv[3]);
		}

	}


	//TODO:
	/*Matrix4<T> inverse()
	{
		Matrix4<T> inv;


		return inv;
	}*/
	Matrix4 translate(double x, double y, double z)
	{
		Matrix4 matrix;
		matrix.set_identity();
		matrix.m[0][3] = x;
		matrix.m[1][3] = y;
		matrix.m[2][3] = z;
		return matrix;
	}
	Matrix4 scale(double x, double y, double z)
	{
		Matrix4 matrix;
		matrix.set_identity();
		matrix.m[0][0] = x;
		matrix.m[1][1] = y;
		matrix.m[2][2] = z;
		return matrix;
	}


	Matrix4 rotate_around_x_axis(double theta)
	{
		Matrix4 matrix;
		matrix.set_identity();
		matrix.m[1][1] = std::cos(theta);
		matrix.m[2][1] = std::sin(theta);
		matrix.m[1][2] = -std::sin(theta);
		matrix.m[2][2] = std::cos(theta);
		return matrix;
	}

	Matrix4 rotate_around_y_axis(double theta)
	{
		Matrix4 matrix;
		matrix.set_identity();
		matrix.m[0][0] = std::cos(theta);
		matrix.m[2][0] = -std::sin(theta);
		matrix.m[0][2] = std::sin(theta);
		matrix.m[2][2] = std::cos(theta);
		return matrix;
	}

	Matrix4 rotate_around_z_axis(double theta)
	{
		Matrix4 matrix;
		matrix.set_identity();
		matrix.m[0][0] = std::cos(theta);
		matrix.m[1][0] = std::sin(theta);
		matrix.m[0][1] = -std::sin(theta);
		matrix.m[1][1] = std::cos(theta);
		return matrix;
	}

	//https://docs.gl/gl2/glRotate
	Matrix4 rotate_round(double theta, Vector3 v)
	{
		Matrix4 matrix;
		matrix.set_identity();

		double c = std::cos(theta);
		double s = std::sin(theta);

		matrix.m[0][0] = v.x * v.x * (1 - c) + c;
		matrix.m[1][0] = v.y * v.x * (1 - c) + v.z * s;
		matrix.m[2][0] = v.x * v.z * (1 - c) - v.y * s;

		matrix.m[0][1] = v.x * v.y * (1 - c) - v.z * s;
		matrix.m[1][1] = v.y * v.y * (1 - c) + c;
		matrix.m[2][1] = v.y * v.z * (1 - c) + v.x * s;

		matrix.m[0][2] = v.x * v.z * (1 - c) + v.y * s;
		matrix.m[1][2] = v.y * v.z * (1 - c) - v.x * s;
		matrix.m[2][2] = v.z * v.z * (1 - c) + c;

		return matrix;
	}

	//================MVP===================
	//reference: games101 lecture 04
	//----------Model---------
	Matrix4 set_model(Vector3 center)
	{
		Matrix4 matrix;
		matrix.set_identity();
		matrix = translate(center.x, center.y, center.z);
		return matrix;
	}
	//----------View----------
	//1. camera position (0,0,0) : e
	//2. look-at/ gaze direction (-z) : g
	//3. up direciton (+y) : t
	//rotation: z to -g, y to t, x to (g.cross(t))

	Matrix4 set_model_view(Vector3 e, Vector3 g, Vector3 t)
	{
		Matrix4 rotate_matrix;
		Matrix4 translate_matrix;
		Matrix4 model_view_matrix;

		rotate_matrix.set_identity();
		g.normalize();
		Vector3 g_cross_t = g.cross(t);
		g_cross_t.normalize();
		t = g_cross_t.cross(g);


		rotate_matrix.m[0][0] = g_cross_t.x;
		rotate_matrix.m[0][1] = g_cross_t.y;
		rotate_matrix.m[0][2] = g_cross_t.z;

		rotate_matrix.m[1][0] = t.x;
		rotate_matrix.m[1][1] = t.y;
		rotate_matrix.m[1][2] = t.z;

		rotate_matrix.m[2][0] = -g.x;
		rotate_matrix.m[2][1] = -g.y;
		rotate_matrix.m[2][2] = -g.z;

		translate_matrix = translate(-e.x, -e.y, -e.z);

		model_view_matrix = rotate_matrix * translate_matrix;

		return model_view_matrix;
	}
	//-------Projection-------
	//1. orthographic projection
	//map a cuboid [l,r]x[b,t]x[f,n] to the canonical cube [-1,1]x[-1,1]x[-1,1]
	Matrix4 orthographic_projection(double l, double r, double b, double t, double f, double n)
	{
		/*Matrix4<T> ortho_translate;
		Matrix4<T> ortho_scale;
		ortho_translate.set_identity();
		ortho_scale.set_identity();
		ortho_translate.m[0][3] = -(r + l) / 2.;
		ortho_translate.m[1][3] = -(t + b) / 2.;
		ortho_translate.m[2][3] = -(n + f) / 2.;
		ortho_scale.m[0][0] = 2. / (r - l);
		ortho_scale.m[1][1] = 2. / (t - b);
		ortho_scale.m[2][2] = 2. / (n - f);
		ortho_matrix = ortho_scale * ortho_translate;*/
		Matrix4 ortho_matrix;
		ortho_matrix.set_identity();
		ortho_matrix.m[0][0] = 2. / (r - l);
		ortho_matrix.m[1][1] = 2. / (t - b);
		ortho_matrix.m[2][2] = 2. / (n - f);
		ortho_matrix.m[0][3] = -(r + l) / 2.;
		ortho_matrix.m[1][3] = -(t + b) / 2.;
		ortho_matrix.m[2][3] = -(n + f) / 2.;
		return ortho_matrix;
	}

	//2. perspective projection
	//from frustum to cuboid:
	//-near plane does not change
	//-far plane's z value does not change, far plane's center point does not change
	Matrix4 perspective_projection(double l, double r, double b, double t, double f, double n)
	{
		/*Matrix4<T> ortho = orthographic_projection(l, r, b, t, f, n);
		Matrix4<T> persp_to_ortho;
		Matrix4<T> persp_matrix;
		persp_to_ortho.m[0][0] = n;
		persp_to_ortho.m[1][1] = n;
		persp_to_ortho.m[3][2] = 1;
		persp_to_ortho.m[2][2] = n + f;
		persp_to_ortho.m[2][3] = -n*f;
		persp_matrix = ortho*persp_to_ortho;*/

		Matrix4 persp_matrix;

		persp_matrix.m[0][0] = 2 * n / (r - l);
		persp_matrix.m[1][1] = 2 * n / (t - b);
		persp_matrix.m[0][2] = (r + l) / (r - l);
		persp_matrix.m[1][2] = (t + b) / (t - b);
		persp_matrix.m[2][2] = (f + n) / (n - f);
		persp_matrix.m[3][2] = 1;
		persp_matrix.m[2][3] = -2 * f * n / (n - f);

		return persp_matrix;

	}

	Matrix4 set_viewport(int width, int height)
	{

		Matrix4 viewport_matrix;
		viewport_matrix.set_identity();

		viewport_matrix.m[0][0] = width / 2.f;
		viewport_matrix.m[1][1] = height / 2.f;
		viewport_matrix.m[0][3] = (width) / 2.f;
		viewport_matrix.m[1][3] = (height) / 2.f;
		//viewport_matrix.m[2][3] = (height + 1) / 2.f;

		return viewport_matrix;
	}

	Matrix4 set_mvp(Vector3 center, Vector3 e, Vector3 g, Vector3 t, double l, double r, double b, double top, double f, double n)
	{
		Matrix4 mv, frustum, mvp;
		mv = set_model_view(e, g, t) * set_model(center);
		frustum = perspective_projection(l, r, b, top, f, n);
		mvp = frustum * mv;
		return mvp;
	}

	friend std::ostream& operator<< (std::ostream& out, const Matrix4& mat);
};


inline std::ostream& operator<< (std::ostream& out, const Matrix4& mat)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out << mat.m[i][j] << ",";
		}
		out << std::endl;
	}
	return out;
}


#endif //__MATHS_H__