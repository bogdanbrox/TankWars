#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "components/simple_scene.h"
#include <vector>
#include <string>

namespace objects2D
{
	std::pair<Mesh*, std::vector<float>> CreateField(
		float width,
		float height,
		glm::vec3 origin,
		std::vector<float> fieldHeightMap = {});
	Mesh* CreateTrapezoid(glm::string name,float width, float height, float topWidth, glm::vec3 color);
	Mesh* CreateSemicircle(glm::string name, float radius, int segments, glm::vec3 color);
	Mesh* CreateRectangle(const std::string& name, float width, float height, glm::vec3 color);
	void SmoothHeightMap(std::vector<float>& heightMap);
	std::vector<float> CubicSplineInterpolation(const std::vector<float>& x, const std::vector<float>& y, int numSamples);
	Mesh* CreateCircle(const std::string& name, float radius, int segments, glm::vec3 color);
	Mesh* CreateLine(const std::string& name, const glm::vec3& color);
	Mesh* CreateEllipse(const std::string& name, float radiusX, float radiusY, glm::vec3 color);
	Mesh* CreateDiamond(glm::string name, float width, float height, glm::vec3 color);
}