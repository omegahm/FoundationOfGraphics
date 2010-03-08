#ifndef FLAT_VERTEX_PROGRAM_H
#define FLAT_VERTEX_PROGRAM_H
//
// Graphics Framework.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen
//
#include "graphics/graphics.h"
#include "solution/toolbox.h"

namespace graphics {

    template<typename math_types>
    class FlatVertexProgram : public VertexProgram<math_types>
    {
    public:
	typedef typename VertexProgram<math_types>::graphics_state_type  graphics_state_type;
	typedef typename math_types::vector3_type                        vector3_type;
	typedef typename math_types::vector4_type						 vector4_type; 

    public:
	void run(graphics_state_type const& state,
		 vector3_type const& in_vertex,
		 vector3_type const& in_color,
		 vector3_type& out_vertex,
		 vector3_type& out_color)
	{
		// >> NO MAGIC HERE <<
		out_vertex = in_vertex;
	    out_color =  in_color;
	}


	void run(graphics_state_type const& state,
		 vector3_type const& in_vertex,
		 vector3_type const& in_normal,
		 vector3_type const& in_color,
		 vector3_type& out_vertex,
		 vector3_type& out_normal,
		 vector3_type& out_color)
	{
	    // >> NO MAGIC HERE <<
	    out_vertex = in_vertex;
	    out_normal = in_normal;
	    out_color  = in_color;
	}
    };

}// end namespace graphics

// FLAT_VERTEX_PROGRAM_H
#endif
