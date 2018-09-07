#pragma once



#include <GL\glew.h>



	//Name after color is just the RGBA and 8 because it is 8 bits per channel 
	struct ColorRGBA8 {

		//create an empty default constructor with an initilzier list for the four variables 
		ColorRGBA8(): r(0), g(0), b(0), a(0) {} 

		//This second constructor is almost the same as the first but takes in four arguments. Note that these Glubyte varaibles 
		//are different from the member variables rgba so name is differently and pass in the members in the arguement 
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {}


	// These are the values for color
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

	};

	struct Position {
		float x;
		float y;
	};

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV {
		float u;
		float v;
	};

	//The vertex definition
	struct Vertex {
		//This is the position struct. When you store a struct or class
		//inside of another struct or class, it is called composition. This is
		//layed out exactly the same in memory as if we had a float position[2],
		//but doing it this way makes more sense.
		Position position;

		//4 bytes for r g b a color.
		Color color;

		//UV texture coordinates.
		UV uv;

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};

