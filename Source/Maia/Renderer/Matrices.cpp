#include "Matrices.hpp"

namespace Maia::Renderer
{
	Eigen::Matrix4f create_orthographic_projection_matrix(Eigen::Vector3f const& dimensions)
	{
		Eigen::Matrix4f value;
		value << 
			2.0f / dimensions(0), 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / dimensions(1), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f / dimensions(2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f;
		return value;
	}

	Eigen::Matrix4f create_perspective_projection_matrix(Eigen::Vector2f const& half_dimensions, Eigen::Vector2f const& zRange)
	{
		float const right = half_dimensions(0);
		float const bottom = half_dimensions(1);
		float const near = zRange(0);
		float const far = zRange(1);

		Eigen::Matrix4f value;
		value <<
			near / right, 0.0f, 0.0f, 0.0f,
			0.0f, near / bottom, 0.0f, 0.0f,
			0.0f, 0.0f, far / (far - near), - far * near / (far - near),
			0.0f, 0.0f, 1.0f, 0.0f;
		return value;
	}

	Eigen::Matrix4f create_perspective_projection_matrix(float const vertical_half_angle_of_view, float const width_by_height_ratio, Eigen::Vector2f const& zRange)
	{
		float const bottom = std::tan(vertical_half_angle_of_view) * zRange(0);
		float const right = width_by_height_ratio * bottom;

		return create_perspective_projection_matrix({ right, bottom }, zRange);
	}
}
