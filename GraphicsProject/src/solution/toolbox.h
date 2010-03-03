#ifndef TOOLBOX
#define TOOLBOX

namespace graphics {
		typedef MyMathTypes::vector3_type   vector3_type;
		typedef MyMathTypes::vector4_type   vector4_type;
		typedef MyMathTypes::matrix4x4_type matrix4x4_type;
		typedef MyMathTypes::real_type      real_type;
		
		/**
		 * Converts from euclidean to homogeneous coordinates
		 */
		vector4_type e2h(vector3_type vector)
		{
			return vector4_type(vector[1], vector[2], vector[3], 1);
		}

		/**
		 * Converts from homogeneous to euclidean coordinates
		 */
		vector3_type h2e(vector4_type vector)
		{
			if( vector[4] == 0) {
				throw std::runtime_error("Toolbox::h2e():Can't divide by zero");
			}
			
			return vector3_type(vector[1] / vector[4], 
			                    vector[2] / vector[4], 
			                    vector[3] / vector[4]);
		}

		/**
		 * Returns a translate matrix, given a vector, with which we move
		 */
		matrix4x4_type translate(vector3_type trans) 
		{
			matrix4x4_type M;
			M[1][1] = 1, M[1][2] = 0, M[1][3] = 0, M[1][4] = trans[1];
		    M[2][1] = 0, M[2][2] = 1, M[2][3] = 0, M[2][4] = trans[2]; 
		    M[3][1] = 0, M[3][2] = 0, M[3][3] = 1, M[3][4] = trans[3]; 
		    M[4][1] = 0, M[4][2] = 0, M[4][3] = 0, M[4][4] = 1;

			return M;
		}

		/**
		 * Returns the inverse translate matrix, given a vector, with which we move
		 */
		matrix4x4_type inv_translate(vector3_type trans) 
		{
			matrix4x4_type M;
			M[1][1] = 1, M[1][2] = 0, M[1][3] = 0, M[1][4] = -trans[1];
		    M[2][1] = 0, M[2][2] = 1, M[2][3] = 0, M[2][4] = -trans[2]; 
		    M[3][1] = 0, M[3][2] = 0, M[3][3] = 1, M[3][4] = -trans[3]; 
		    M[4][1] = 0, M[4][2] = 0, M[4][3] = 0, M[4][4] = 1;

			return M;
		}

		/**
		 * Returns a scaling matrix, given a vector, with which we scale
		 */
		matrix4x4_type scale(vector3_type sc) 
		{
			matrix4x4_type M;
			M[1][1] = sc[1], M[1][2] = 0,     M[1][3] = 0,     M[1][4] = 0;
		    M[2][1] = 0,     M[2][2] = sc[2], M[2][3] = 0,     M[2][4] = 0; 
		    M[3][1] = 0,     M[3][2] = 0,     M[3][3] = sc[3], M[3][4] = 0; 
		    M[4][1] = 0,     M[4][2] = 0,     M[4][3] = 0,     M[4][4] = 1;

			return M;
		}

		/**
		 * Returns the inverse scaling matrix, given a vector, with which we scale
		 */
		matrix4x4_type inv_scale(vector3_type sc) 
		{
			matrix4x4_type M;
			M[1][1] = 1/sc[1], M[1][2] = 0,       M[1][3] = 0,       M[1][4] = 0;
		    M[2][1] = 0,       M[2][2] = 1/sc[2], M[2][3] = 0,       M[2][4] = 0; 
		    M[3][1] = 0,       M[3][2] = 0,       M[3][3] = 1/sc[3], M[3][4] = 0; 
		    M[4][1] = 0,       M[4][2] = 0,       M[4][3] = 0,       M[4][4] = 1;

			return M;
		}

		/**
		 * Returns the X-rotation matrix, given a radian, with which we rotate
		 */
		matrix4x4_type x_rotate(real_type r) 
		{
			matrix4x4_type M;
			M[1][1] = 1, M[1][2] = 0,      M[1][3] = 0,       M[1][4] = 0;
		    M[2][1] = 0, M[2][2] = cos(r), M[2][3] = -sin(r), M[2][4] = 0; 
		    M[3][1] = 0, M[3][2] = sin(r), M[3][3] = cos(r),  M[3][4] = 0; 
		    M[4][1] = 0, M[4][2] = 0,      M[4][3] = 0,       M[4][4] = 1;

			return M;
		}

		/**
		 * Returns the inverse X-rotation matrix, given a radian, with which we rotate
		 */
		matrix4x4_type inv_x_rotate(real_type r) 
		{
			matrix4x4_type M;
			M[1][1] = 1, M[1][2] = 0,       M[1][3] = 0,      M[1][4] = 0;
		    M[2][1] = 0, M[2][2] = cos(r),  M[2][3] = sin(r), M[2][4] = 0; 
		    M[3][1] = 0, M[3][2] = -sin(r), M[3][3] = cos(r), M[3][4] = 0; 
		    M[4][1] = 0, M[4][2] = 0,       M[4][3] = 0,      M[4][4] = 1;

			return M;
		}

		/**
		 * Returns the Y-rotation matrix, given a radian, with which we rotate
		 */
		matrix4x4_type y_rotate(real_type r) 
		{
			matrix4x4_type M;
			M[1][1] = cos(r),  M[1][2] = 0, M[1][3] = sin(r), M[1][4] = 0;
		    M[2][1] = 0,       M[2][2] = 1, M[2][3] = 0,      M[2][4] = 0; 
		    M[3][1] = -sin(r), M[3][2] = 0, M[3][3] = cos(r), M[3][4] = 0; 
		    M[4][1] = 0,       M[4][2] = 0, M[4][3] = 0,      M[4][4] = 1;

			return M;
		}

		/**
		 * Returns the inverse Y-rotation matrix, given a radian, with which we rotate
		 */
		matrix4x4_type inv_y_rotate(real_type r) 
		{
			matrix4x4_type M;
			M[1][1] = cos(r), M[1][2] = 0, M[1][3] = -sin(r), M[1][4] = 0;
		    M[2][1] = 0,      M[2][2] = 1, M[2][3] = 0,       M[2][4] = 0; 
		    M[3][1] = sin(r), M[3][2] = 0, M[3][3] = cos(r),  M[3][4] = 0; 
		    M[4][1] = 0,      M[4][2] = 0, M[4][3] = 0,       M[4][4] = 1;

			return M;
		}

		/**
		 * Returns the Z-rotation matrix, given a radian, with which we rotate
		 */
		matrix4x4_type z_rotate(real_type r) 
		{
			matrix4x4_type M;
			M[1][1] = cos(r), M[1][2] = -sin(r), M[1][3] = 0, M[1][4] = 0;
		    M[2][1] = sin(r), M[2][2] = cos(r),  M[2][3] = 0, M[2][4] = 0; 
		    M[3][1] = 0,      M[3][2] = 0,       M[3][3] = 1, M[3][4] = 0; 
		    M[4][1] = 0,      M[4][2] = 0,       M[4][3] = 0, M[4][4] = 1;
	
			return M;
		}

		/**
		 * Returns the inverse Z-rotation matrix, given a radian, with which we rotate
		 */
		matrix4x4_type inv_z_rotate(real_type r) 
		{
			matrix4x4_type M;
			M[1][1] = cos(r),  M[1][2] = sin(r), M[1][3] = 0, M[1][4] = 0;
		    M[2][1] = -sin(r), M[2][2] = cos(r), M[2][3] = 0, M[2][4] = 0; 
		    M[3][1] = 0,       M[3][2] = 0,      M[3][3] = 1, M[3][4] = 0; 
		    M[4][1] = 0,       M[4][2] = 0,      M[4][3] = 0, M[4][4] = 1;

			return M;
		}
		
		/**
		 * Free rotate, given 3 rowvectors
		 */
		matrix4x4_type rotate(vector3_type x, vector3_type y, vector3_type z)
		{
			matrix4x4_type M;
			M[1][1] = x[1], M[1][2] = x[2], M[1][3] = x[3], M[1][4] = 0;
		    M[2][1] = y[1], M[2][2] = y[2], M[2][3] = y[3], M[2][4] = 0; 
		    M[3][1] = z[1], M[3][2] = z[2], M[3][3] = z[3], M[3][4] = 0; 
		    M[4][1] = 0,    M[4][2] = 0,    M[4][3] = 0,    M[4][4] = 1;
		
			return M;
		}

		/**
		 * Returns the XY-shear matrix, given the shear factors
		 */
		matrix4x4_type xy_shear(real_type shx, real_type shy) 
		{
			matrix4x4_type M;
			M[1][1] = 1, M[1][2] = 0, M[1][3] = shx, M[1][4] = 0;
		    M[2][1] = 0, M[2][2] = 1, M[2][3] = shy, M[2][4] = 0; 
		    M[3][1] = 0, M[3][2] = 0, M[3][3] = 1,   M[3][4] = 0; 
		    M[4][1] = 0, M[4][2] = 0, M[4][3] = 0,   M[4][4] = 1;
	
			return M;
		}

		/**
		 * Returns the inverse XY-shear matrix, given the shear factors
		 */
		matrix4x4_type inv_xy_shear(real_type shx, real_type shy) 
		{
			matrix4x4_type M;
			M[1][1] = 1, M[1][2] = 0, M[1][3] = -shx, M[1][4] = 0;
		    M[2][1] = 0, M[2][2] = 1, M[2][3] = -shy, M[2][4] = 0; 
		    M[3][1] = 0, M[3][2] = 0, M[3][3] = 1,    M[3][4] = 0; 
		    M[4][1] = 0, M[4][2] = 0, M[4][3] = 0,    M[4][4] = 1;
	
			return M;
		}

		/**
		 * Returns the XZ-shear matrix, given the shear factors
		 */
		matrix4x4_type xz_shear(real_type shx, real_type shz) 
		{
			matrix4x4_type M;
			M[1][1] = 1, M[1][2] = shx, M[1][3] = 0, M[1][4] = 0;
		    M[2][1] = 0, M[2][2] = 1,   M[2][3] = 0, M[2][4] = 0; 
		    M[3][1] = 0, M[3][2] = shz, M[3][3] = 1, M[3][4] = 0; 
		    M[4][1] = 0, M[4][2] = 0,   M[4][3] = 0, M[4][4] = 1;
	
			return M;
		}

		/**
		 * Returns the inverse XZ-shear matrix, given the shear factors
		 */
		matrix4x4_type inv_xz_shear(real_type shx, real_type shz) 
		{
			matrix4x4_type M;
			M[1][1] = 1, M[1][2] = -shx, M[1][3] = 0, M[1][4] = 0;
		    M[2][1] = 0, M[2][2] = 1,    M[2][3] = 0, M[2][4] = 0; 
		    M[3][1] = 0, M[3][2] = -shz, M[3][3] = 1, M[3][4] = 0; 
		    M[4][1] = 0, M[4][2] = 0,    M[4][3] = 0, M[4][4] = 1;
	
			return M;
		}

		/**
		 * Returns the YZ-shear matrix, given the shear factors
		 */
		matrix4x4_type yz_shear(real_type shy, real_type shz) 
		{
			matrix4x4_type M;
			M[1][1] = 1,   M[1][2] = 0, M[1][3] = 0, M[1][4] = 0;
		    M[2][1] = shy, M[2][2] = 1, M[2][3] = 0, M[2][4] = 0; 
		    M[3][1] = shz, M[3][2] = 0, M[3][3] = 1, M[3][4] = 0; 
		    M[4][1] = 0,   M[4][2] = 0, M[4][3] = 0, M[4][4] = 1;
	
			return M;
		}

		/**
		 * Returns the inverse YZ-shear matrix, given the shear factors
		 */
		matrix4x4_type inv_yz_shear(real_type shy, real_type shz) 
		{
			matrix4x4_type M;
			M[1][1] = 1,    M[1][2] = 0, M[1][3] = 0, M[1][4] = 0;
		    M[2][1] = -shy, M[2][2] = 1, M[2][3] = 0, M[2][4] = 0; 
		    M[3][1] = -shz, M[3][2] = 0, M[3][3] = 1, M[3][4] = 0; 
		    M[4][1] = 0,    M[4][2] = 0, M[4][3] = 0, M[4][4] = 1;
	
			return M;
		}
}

#endif