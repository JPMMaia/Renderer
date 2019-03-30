#ifndef MAIA_RENDERER_MATRICES_H_INCLUDED
#define MAIA_RENDERER_MATRICES_H_INCLUDED

#include <Eigen/Geometry>

namespace Maia::Renderer
{
	Eigen::Matrix4f create_view_matrix(Eigen::Vector3f const& position, Eigen::Quaternionf const& rotation);
	
	Eigen::Matrix4f create_orthographic_projection_matrix(float horizontal_magnification, float vertical_magnification, float near_z, float far_z);
	
	Eigen::Matrix4f create_perspective_projection_matrix(Eigen::Vector2f const& half_dimensions, Eigen::Vector2f const& zRange);
	Eigen::Matrix4f create_perspective_projection_matrix(float vertical_half_angle_of_view, float width_by_height_ratio, Eigen::Vector2f const& zRange);
}

#endif
