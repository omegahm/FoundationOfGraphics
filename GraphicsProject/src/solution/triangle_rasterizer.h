#ifndef TRIANGLE_RASTERIZER_H
#define TRIABGLE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include "graphics/graphics.h"
#include "edge_rasterizer.h"
// #include "linear_interpolator"



namespace graphics {

	template<typename math_types>
	class MyTriangleRasterizer : public Rasterizer<math_types>
	{
	public:
		typedef typename math_types::vector3_type vector3_type;
		typedef typename math_types::real_type    real_type;

	protected:


	public:
		MyTriangleRasterizer() : valid(false), Debug(false)
			{}


		virtual ~MyTriangleRasterizer()
			{}


		void init( vector3_type const& in_vertex1,
			vector3_type const& in_normal1,
			vector3_type const& in_color1,
			vector3_type const& in_vertex2,
			vector3_type const& in_normal2,
			vector3_type const& in_color2,
			vector3_type const& in_vertex3,
			vector3_type const& in_normal3,
			vector3_type const& in_color3) 
		{
		// This is a triangle rasterizer
			this->vertices[0] = in_vertex1;
			this->vertices[1] = in_vertex2;
			this->vertices[2] = in_vertex3;

			this->normals[0]  = in_normal1; 
			this->normals[1]  = in_normal2; 
			this->normals[2]  = in_normal3; 

			this->colors[0]   = in_color1; 
			this->colors[1]   = in_color2; 
			this->colors[2]   = in_color3; 

			int ulindex       = this->UpperLeft();
			int ulx           = this->vertices[ulindex][1];
			int uly           = this->vertices[ulindex][2];

			int llindex       = this->LowerLeft();
			int llx           = this->vertices[llindex][1];
			int lly           = this->vertices[llindex][2];

			int otherindex    = 3 - llindex - ulindex;
			int otherx        = this->vertices[otherindex][1];
			int othery        = this->vertices[otherindex][2];
			this->the_other   = otherindex;

			/**
			* What type are we???
			*
			* To find the type, we take the cross product of the to edges.
			* If this is zero the triangle is degenerate, if it is above
			* we have the other to the left. Below zero we have it to the right.
			*/
			int type = (ulx - llx) * (othery - lly) - (otherx - llx) * (uly - lly);

			if( type != 0 && lly == othery ) {

				this->left.init( this->vertices[llindex],
					this->normals[llindex],
					this->colors[llindex],
					this->vertices[ulindex],
					this->normals[ulindex],
					this->colors[ulindex] );

				this->right.init( this->vertices[otherindex],
					this->normals[otherindex],
					this->colors[otherindex],
					this->vertices[ulindex],
					this->normals[ulindex],
					this->colors[ulindex] );
			} else if( type != 0 && uly == othery ) {

				this->left.init( this->vertices[llindex],
					this->normals[llindex],
					this->colors[llindex],
					this->vertices[ulindex],
					this->normals[ulindex],
					this->colors[ulindex] );

				this->right.init( this->vertices[llindex],
					this->normals[llindex],
					this->colors[llindex], 
					this->vertices[otherindex],
					this->normals[otherindex],
					this->colors[otherindex] );
			} else {
				if( type == 0 ) {
					this->valid = false;
					return;
				} else if( type > 0 ) {
						// We have two edges to the left

					this->left.init( this->vertices[llindex], 
						this->normals[llindex],
						this->colors[llindex], 
						this->vertices[otherindex],                                 
						this->normals[otherindex],
						this->colors[otherindex],
						this->vertices[ulindex],
						this->normals[ulindex],
						this->colors[ulindex] );

					this->right.init( this->vertices[llindex],
						this->normals[llindex],
						this->colors[llindex],
						this->vertices[ulindex],
						this->normals[ulindex],
						this->colors[ulindex] ); 

				} else {
						// We have two edges to the right
					this->left.init( this->vertices[llindex],
						this->normals[llindex],
						this->colors[llindex],
						this->vertices[ulindex],
						this->normals[ulindex],
						this->colors[ulindex] );

					this->right.init( this->vertices[llindex], 
						this->normals[llindex],
						this->colors[llindex], 
						this->vertices[otherindex],                                 
						this->normals[otherindex],
						this->colors[otherindex],
						this->vertices[ulindex],
						this->normals[ulindex],
						this->colors[ulindex] );
				}
			}


			this->Debug = false;
			this->valid = true;
			this->initialize_triangle();

			/* The first scanline is almost always empty!
			* it is either a horizontal line,
			* or a scanline with one dot, which
			* has to be part of both a left and 
			* right edge.
			* 
			* The horizontal line is drawn, the other is skipped
			*/
			this->x_current = this->left.x();
		this->y_current = this->left.y();

		if( lly != othery ) {
			this->valid = this->SearchForNonEmptyScanline(); 
		} else {
			this->valid = true;
		}
	}

	bool DebugOn()
	{
		bool oldvalue = this->Debug;
		this->Debug = true;

		return oldvalue;
	}

	bool DebugOff()
	{
		bool oldvalue = this->Debug;
		this->Debug = false;

		return oldvalue;
	}

	bool Valid() const
	{
		// implement the real version
		return true;
	}

	bool Degenerate() const
	{
		// implement the real version
		return false;
	}

	int x() const      
	{
		if (!this->valid) {
			throw std::runtime_error("MyTriangleRasterizer::x():Invalid State/Not Initialized");
		}
		// implement the real version
		return this->x_current;
	}

	int y() const
	{
		if (!this->valid) {
			throw std::runtime_error("MyTriangleRasterizer::y():Invalid State/Not Initialized");
		}
		// implement the real version
		return this->y_current;
	}

	real_type depth() const     
	{
		if (!this->valid) {
			throw std::runtime_error("MyTriangleRasterizer::depth():Invalid State/Not Initialized");
		}
		// implement the real version
		return 0.0;
	}

	vector3_type position() const 
	{
		if (!this->valid) {
			throw std::runtime_error("MyTriangleRasterizer::position():Invalid State/Not Initialized");
		}
		return vector3_type(this->x(), this->y(), this->depth());
	}

	vector3_type const& normal() const     
	{
		if (!this->valid) {
			throw std::runtime_error("MyTriangleRasterizer::normal():Invalid State/Not Iitialized");
		}
		// implement the real version
		return this->dummy_vector;    
	}

	vector3_type const& color() const 
	{
		if (!this->valid) {
			throw std::runtime_error("MyTriangleRasterizer::color():Invalid State/Not Initialized");
		}
		// implement the real version
		return this->dummy_vector;
	}

	void print_variables()
	{
		std::cout << "MyTriangleRasterizer: local variables" << std::endl;
		std::cout << "=====================================" << std::endl;
		std::cout << "\tvalid     == " << this->valid    << std::endl;
		std::cout << std::endl;
	}


/*******************************************************************\
*                                                                   *
*                  m o r e _ f r a g m e n t s ( )                  *
*                                                                   *
\*******************************************************************/

bool more_fragments() const 
{
	return this->valid;
}


/*******************************************************************\
*                                                                   *
*                   n e x t _ f r a g m e n t ( )                   *
*                                                                   *
\*******************************************************************/

void next_fragment()    
{
	if( this->valid && this->left.more_fragments() && this->right.more_fragments() ) {
		if( this->y_current > this->left.y() && this->y_current > this->right.y() ) {
			this->valid = false;
		} else if( this->x_current >= this->right.x() - 1 ) {
					// We have reached the last pixel in the scanline
			if( !this->SearchForNonEmptyScanline() ) {
				this->valid = false;
			}
		} else {
			this->x_current += 1;
		}
	} else {
		this->valid = false; 
	}
}



private:
	// Initialize the current triangle for rasterization
	void initialize_triangle()
	{
		// implement the real version
		this->valid = true;    // necessary?
	}


	// A triangle is degenerate if all three points are co-linear
	bool degenerate()
	{
		return false;
	}


	// LowerLeft() returns the index of the vertex with the smallest y-coordinate
	// If there is a horizontal edge, the vertex with the smallest 
	// x-coordinate is chosen.
	// The computations should be done in integer coordinates.
	int LowerLeft()
	{
		int ll = 0;

		for( int i = ll + 1; i < 3; ++i ) {
			if( ( this->vertices[i][2] < this->vertices[ll][2] ) || 
			( this->vertices[i][2] == this->vertices[ll][2] ) && ( this->vertices[i][1] < this->vertices[ll][1] ) ) {
				ll = i;
			}
		}

		return ll;
	}

	// UpperLeft() returns the index of the vertex with the greatest y-coordinate
	// If there is a horizontal edge, the vertex with the smallest 
	// x-coordinate is chosen.
	// The computations should be done in integer coordinates.
	int UpperLeft()
	{
		int ul = 0;

		for( int i = ul + 1; i < 3; ++i ) {
			if( ( this->vertices[i][2] > this->vertices[ul][2] ) || 
			( this->vertices[i][2] == this->vertices[ul][2] ) && ( this->vertices[i][1] < this->vertices[ul][1] ) ) {
				ul = i;
			}
		}

		return ul; 
	}


	bool SearchForNonEmptyScanline()
	{
		// Assumes that the current scanline is empty!
		do {
			this->left.next_fragment();
			this->right.next_fragment();

			if( this->left.more_fragments() && this->right.more_fragments() ) {
				this->x_current = this->left.x();
				this->y_current = this->left.y();
			} else {
				break;
			}
		} while( this->x_current > this->right.x() - 1 );

		return this->valid && this->left.more_fragments() && this->right.more_fragments();
	}


	void choose_color(int x)
	{
		// x is the position on a scanline in a triangle - they all have different colors:
		//    xstart  : green
		//    xcurrent: yellow
		//    xstop   : red
		// This is like a trafic-light: green->go ahead, yellow->be carefull, red->stop!

		// implement the real version
	}


	// Private Variables

	vector3_type dummy_vector;
	vector3_type vertices[3];
	vector3_type colors[3];
	vector3_type normals[3];

	MyEdgeRasterizer<math_types> left;
	MyEdgeRasterizer<math_types> right;
	// The Debug variable
	bool Debug;

	// Indices into the vertex table
	int lower_left;
	int upper_left;
	int the_other;

	int x_current;
	int y_current;
	bool valid;
};

}// end namespace graphics

// TRIANGLE_RASTERIZER_H
#endif
