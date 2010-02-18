#ifndef EDGE_RASTERIZER_H
#define EDGE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include "graphics/graphics.h"

namespace graphics {

    // Draws an edge from V1 to V2, or two edges - one from V1 to V2 and one from V2 to V3.
    // Edges are assumed NOT to be horizontal!
    template<typename math_types>
    class MyEdgeRasterizer
    {
    public:
	typedef typename math_types::real_type    real_type;
	typedef typename math_types::vector3_type vector3_type;

    public:
	MyEdgeRasterizer() : valid(false)
	{
	    std::cout << "MyEdgeRasterizer::MyEdgeRasterizer(): called" << std::endl;
	}

	virtual ~MyEdgeRasterizer()
	{}

	void init(vector3_type const& in_vertex1,
		  vector3_type const& in_normal1,
		  vector3_type const& in_color1,
		  vector3_type const& in_vertex2,
		  vector3_type const& in_normal2,
		  vector3_type const& in_color2)
        {
	    // Save the original parameters

	    std::cout << "edge_rasterizer::init(...) - One Edge" << std::endl;
	    
            this->vertices[0] = in_vertex1;
            this->vertices[1] = in_vertex2;

	    this->two_edges = false;
	    this->init_edge( 0, 1 );
	    this->valid = true;
        }
	
	void init(vector3_type const& in_vertex1,
		  vector3_type const& in_normal1,
		  vector3_type const& in_color1,
		  vector3_type const& in_vertex2,
		  vector3_type const& in_normal2,
		  vector3_type const& in_color2,
		  vector3_type const& in_vertex3,
		  vector3_type const& in_normal3,
		  vector3_type const& in_color3)
        {
	    // Save the original parameters

	    std::cout << "edge_rasterizer::init(...) - Two Edges" << std::endl;
            this->vertices[0] = in_vertex1;
            this->vertices[1] = in_vertex2;
            this->vertices[2] = in_vertex3;

	    this->two_edges = true;
 
            this->init_edge(0, 1);
 
	    this->valid = true;
        }
	

	int x() const
	{
	    if (!this->valid) {
		throw std::runtime_error("MyEdgeRasterizer::x():Invalid State/Not Initialized");
            }
	    return this->x_current;
	}

	int y() const
	{
	    if (!this->valid) {
		throw std::runtime_error("MyEdgeRasterizer::y():Invalid State/Not Initialized");
            }
	    return this->y_current;
	}

	real_type depth() const
	{
	    if (!this->valid) {
		throw std::runtime_error("MyEdgeRasterizer::depth():Invalid State/Not Initialized");
            }
	    return 0;
	}

	vector3_type position() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::position():Invalid State/Not Initialized");
            }
            return vector3_type(this->x(), this->y(), this->depth());
        }

	vector3_type normal() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::normal():Invalid State/Not Initialized");
            }
            return vector3_type(0.0, 0.0, 0.0);
        }

	vector3_type color() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::color():Invalid State/Not Initialized");
            }
            return vector3_type(0.0, 0.0, 0.0);
        }

	void print_variables()
        {
	    std::cout << "MyEdgeRasterizer: local variables" << std::endl;
	    std::cout << "=================================" << std::endl;
	    std::cout << std::endl;
	}

	bool more_fragments() const
	{
	    return this->valid;
	}

	void next_fragment()
        {
	    this->y_current += this->y_step;
            if( this->y_current >= this->y_stop ) {
                if( !( this->two_edges ) ) {
                    this->valid = false;
                } else {
                    this->init_edge( 1, 2 );
                    this->two_edges = false;
                }
            } else {
                this->update_edge();
            }
        }

    protected:

    private:
        void init_edge( int vertex1, int vertex2 )
        {
            vector3_type first  = this->vertices[vertex1];
	    vector3_type second = this->vertices[vertex2];

            this->x_start       = first[1];
            this->y_start       = first[2];

	    this->x_stop        = second[1];
            this->y_stop        = second[2];

            this->x_current     = this->x_start;
            this->y_current     = this->y_start;
            
            this->dx            = this->x_stop - this->x_start;
            this->dy            = this->y_stop - this->y_start;

            this->x_step        = ( this->dx < 0 ) ? -1 : 1;
            this->y_step        = 1;

            this->numerator     = std::abs( this->dx );
            this->denominator   = this->dy;
            this->accumulator   = ( this->x_step > 0 ) ? this->denominator : 1;

	    this->valid         = ( this->y_current < this->y_stop ); 
        }

        void update_edge() 
        {
            this->accumulator += this->numerator;
            while( this->accumulator > this->denominator ) {
                this->x_current   += this->x_step;
                this->accumulator -= this->denominator;
            }
        }
	
	vector3_type vertices[3];
	bool valid;
	bool two_edges;
	
	int x_start;
	int y_start;

	int x_stop;
	int y_stop;

	int x_current;
	int y_current;

	int dx;
	int dy;

	int x_step;
	int y_step;

	int numerator;
	int denominator;
	int accumulator;

        int prior_edge;
        int next_edge;

    };

}// end namespace graphics

// EDGE_RASTERIZER_H
#endif
