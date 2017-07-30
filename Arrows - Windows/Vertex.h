#ifndef VERTEX_H_
#define VERTEX_H_

#include <GL/glew.h>

struct Position{
	float x;
	float y;
	float z;
};

struct Color {
	Color() : r(0), g(0), b(0), a(0) { }
	Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : 
		r(R), g(G), b(B), a(A) { }
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV {
	float u;
	float v;
};

struct Vertex {

	Position position;
	Color color;
	UV uv;

	void setPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}
	
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
	
	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}

	void setPosUV(float x, float y, float z, float u, float v)
	{
		position.x = x;
		position.y = y;
		position.z = z;
		uv.u = u;
		uv.v = v;
	}
};

#endif
