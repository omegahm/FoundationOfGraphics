#ifndef LINE_RASTERIZER_H
#define LINE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <cmath>

#include "graphics/graphics.h"
#include "linear_interpolator.h"


/*******************************************************************\
*                                                                   *
*                N a m e S p a c e   g r a p h i c s                *
*                                                                   *
\*******************************************************************/

namespace graphics {

/*******************************************************************\
*                                                                   *
*            C l a s s   M y L i n e R a s t e r i z e r            *
*                                                                   *
\*******************************************************************/

    template<typename math_types>
    class MyLineRasterizer : public Rasterizer<math_types>
    {

/*******************************************************************\
*                                                                   *
*                       P u l i c   T y p e s                       *
*                                                                   *
\*******************************************************************/

    public:

/*******************************************************************\
*                                                                   *
*                      v e c t o r 3 _ t y p e                      *
*                                                                   *
\*******************************************************************/

	typedef typename math_types::vector3_type      vector3_type;

/*******************************************************************\
*                                                                   *
*                         r e a l _ t y p e                         *
*                                                                   *
\*******************************************************************/

	typedef typename math_types::real_type         real_type;



/*******************************************************************\
*                                                                   *
*                    P u b l i c   M e m b e r s                    *
*                                                                   *
\*******************************************************************/

    public:

/*******************************************************************\
*                                                                   *
*                M y L i n e R a s t e r i z e r ( )                *
*                                                                   *
\*******************************************************************/

	MyLineRasterizer() : Debug(false), valid(false)
	{}


/*******************************************************************\
*                                                                   *
*                ~ M y L i n e R a s t e r i z e r ( )              *
*                                                                   *
\*******************************************************************/

	virtual ~MyLineRasterizer() {}


/*******************************************************************\
*                                                                   *
*           i n i t ( 4   x   v e c t o r 3 _ t y p e & )           *
*                                                                   *
\*******************************************************************/

	void init( vector3_type const& in_vertex1,
		   vector3_type const& in_color1,
		   vector3_type const& in_vertex2,
		   vector3_type const& in_color2)
	{
	    // This is a line rasterizer
	    // The vertices are in 3D screen coordinates
	    this->x_start   = in_vertex1[1];
	    this->y_start   = in_vertex1[2];
	    
	    this->x_stop    = in_vertex2[1];
	    this->y_stop    = in_vertex2[2];

	    this->x_current = this->x_start;
	    this->y_current = this->y_start;

	    int dx	    = this->x_stop - this->x_start;
	    int dy	    = this->y_stop - this->y_start;

	    this->abs_2dx   = std::abs( dx ) << 1; // 2 * |dx|
	    this->abs_2dy   = std::abs( dy ) << 1; // 2 * |dy|

	    this->x_step    = ( dx < 0 ) ? -1 : 1;
	    this->y_step    = ( dy < 0 ) ? -1 : 1;

	    this->color_start   = in_color1;
	    this->color_stop    = in_color2;
	    this->color_current = color_start;
	    
	    // Determine if the line is x-dominat or y-dominant
	    if ( this->abs_2dx > this->abs_2dy )
	    {
		// The line is x-dominant
		this->left_right = ( this->x_step > 0 );
		this->d          = this->abs_2dy - ( this->abs_2dx >> 1 );
		this->valid      = ( this->x_start != this->x_stop );

		this->innerloop = &MyLineRasterizer::x_dominant_innerloop;
	    }
	    else {
		// The line is y-dominant
		this->left_right = ( this->y_step > 0 );
		this->d          = this->abs_2dx - ( this->abs_2dy >> 1 );
		this->valid      = ( this->y_start != this->y_stop );

		this->innerloop = &MyLineRasterizer::y_dominant_innerloop;
	    }

	    this->Debug = false;
	    this->valid = true;

	}


/*******************************************************************\
*                                                                   *
*                         D e b u g O n ( )                         *
*                                                                   *
\*******************************************************************/

	bool DebugOn()
	{
	    bool oldvalue = this->Debug;
	    this->Debug = true;

	    return oldvalue;
	}

/*******************************************************************\
*                                                                   *
*                        D e b u g O f f ( )                        *
*                                                                   *
\*******************************************************************/

	bool DebugOff()
	{
	    bool oldvalue = this->Debug;
	    this->Debug = false;

	    return oldvalue;
	}

/*******************************************************************\
*                                                                   *
*                               x ( )                               *
*                                                                   *
\*******************************************************************/

	int x() const
	{
	    if (!this->valid) {
		throw std::runtime_error("MyLineRasterizer::x():Invalid State/Not Initialized");
	    }
	    return this->x_current;     
	}


/*******************************************************************\
*                                                                   *
*                               y ( )                               *
*                                                                   *
\*******************************************************************/

	int y() const
	{
	    if (!this->valid) {
		throw std::runtime_error("MyLineRasterizer::y():Invalid State/Not Initialized");
	    }
	    return this->y_current;
	}


/*******************************************************************\
*                                                                   *
*                           d e p t h ( )                           *
*                                                                   *
\*******************************************************************/

	real_type depth() const     
	{
	    if (!this->valid) {
		throw std::runtime_error("MyLineRasterizer::depth():Invalid State/Not Initialized");
	    }
	    return 0.0;
	}


/*******************************************************************\
*                                                                   *
*                        p o s i t i o n ( )                        *
*                                                                   *
\*******************************************************************/

	vector3_type position() const 
        {
	    if (!this->valid) {
		throw std::runtime_error("MyLineRasterizer::position():Invalid State/Not Initialized");
	    }
	    return vector3_type(this->x(), this->y(), this->depth());
	}


/*******************************************************************\
*                                                                   *
*                          n o r m a l ( )                          *
*                                                                   *
\*******************************************************************/

	vector3_type const& normal() const     
	{
	    if (!this->valid) {
		throw std::runtime_error("MyLineRasterizer::normal():Invalid State/Not Initialized");
	    }
	    return this->dummy_vector;    // The program should never come here!
	}


/*******************************************************************\
*                                                                   *
*                           c o l o r ( )                           *
*                                                                   *
\*******************************************************************/

	vector3_type const& color() const 
	{
	    if (!this->valid) {
		throw std::runtime_error("MyLineRasterizer::color():Invalid State/Not Initialized");
	    }
	    return this->color_current;
	}


/*******************************************************************\
*                                                                   *
*                  m o r e _ f r a g m e n t s ( )                  *
*                                                                   *
\*******************************************************************/
	

	bool more_fragments() const 
	{
            // Usage:
	    //    Assume a pointer variable rasterizer is set up probably
	    //     while (rasterizer->more_fragments()) {
	    //         int x = rasterize->x();
	    //         int y = rasterizer->y();
	    //         MyMathTypes::real_type depth = rasterizer->depth();
	    //         MyMathTypes::vector3_type    = rasterizer->position();
	    //         MyMathTypes::vector3_type    = rasterizer->color();
	    //             ...
	    //             use the values ...
	    //             ...
	    //         rasterizer->next_fragment();
	    //    }

	    return this->valid;
	}


/*******************************************************************\
*                                                                   *
*                   n e x t _ f r a g m e n t ( )                   *
*                                                                   *
\*******************************************************************/

	void next_fragment()    
	{
	    // Dereference a pointer to a private member function.
	    // It looks strange, but it is the way to do it!
	    (this->*innerloop)();
     	}


/*******************************************************************\
*                                                                   *
*                 p r i n t _ v a r i a b l e s ( )                 *
*                                                                   *
\*******************************************************************/

	void print_variables()
	{
	    std::cout << "MyLineRasterizer: local variables" << std::endl;
	    std::cout << "=================================" << std::endl;
	    std::cout << "\tvalid     == " << this->valid    << std::endl;
	}

    protected:


/*******************************************************************\
*                                                                   *
*                   P r i v a t e   M e m b e r s                   *
*                                                                   *
\*******************************************************************/

    private:


/*******************************************************************\
*                                                                   *
*                x _ d o m i n a n t _ i n n e r l o o p ( )        *
*                                                                   *
\*******************************************************************/

	void x_dominant_innerloop()
	{
	    if ( this->x_current == this->x_stop ) 
	    {
		this->valid = false;
	    } else 
	    {
		if ( ( this->d > 0 ) || ( ( this->d == 0 ) && this->left_right ) ) 
		{
		    this->y_current += this->y_step;
		    this->d         -= this->abs_2dx;
		}
		this->x_current += this->x_step;
		this->d         += this->abs_2dy;
	    }
	}


/*******************************************************************\
*                                                                   *
*            y _ d o m i n a n t _ i n n e r l o o p ( )            *
*                                                                   *
\*******************************************************************/

	void y_dominant_innerloop()
	{
	    if ( this->y_current == this->y_stop ) 
	    {
		this->valid = false;
	    } else 
	    {
		if ( ( this->d > 0 ) || ( ( this->d == 0 ) && this->left_right ) ) 
		{
		    this->x_current += this->x_step;
		    this->d         -= this->abs_2dy;
		}
		this->y_current += this->y_step;
		this->d         += this->abs_2dx;
	    }
	}

/*******************************************************************\
*                                                                   *
*                 P r i v a t e   V a r i a b l e s                 *
*                                                                   *
\*******************************************************************/

	// This looks strange, byt it is the definition of a pointer to a 
	// private member function! That is how it is done!
	void         (MyLineRasterizer::*innerloop)();

	bool         valid;

	bool         Debug;

	vector3_type dummy_vector;
	
	vector3_type color_start;
	vector3_type color_stop;
	vector3_type color_current;

	int	     x_start;
	int	     x_stop;

	int	     y_start;
	int	     y_stop;

	int	     x_current;
	int	     y_current;

	int	     x_step;
	int	     y_step;
	
	int	     abs_2dx;
	int	     abs_2dy;

	int	     d;

	bool	     left_right;
    };

}// end namespace graphics

// LINE_RASTERIZER_H
#endif
