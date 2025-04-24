#include "objects2D.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "components/simple_scene.h"
#include "tema1.h"
#include <string>

std::vector<float> objects2D::CubicSplineInterpolation(const std::vector<float>& x, const std::vector<float>& y, int numSamples) {
    int n = x.size();
    std::vector<float> a = y;
    std::vector<float> b(n - 1), d(n - 1), h(n - 1);

    for (int i = 0; i < n - 1; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    std::vector<float> alpha(n - 1);
    for (int i = 1; i < n - 1; ++i) {
        alpha[i] = (3 * (a[i + 1] - a[i]) / h[i]) - (3 * (a[i] - a[i - 1]) / h[i - 1]);
    }

    std::vector<float> c(n), l(n), mu(n), z(n);
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n - 1] = 1;
    z[n - 1] = 0;
    c[n - 1] = 0;

    for (int j = n - 2; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    std::vector<float> interpolatedY(numSamples);
    float dx = (x.back() - x.front()) / (numSamples - 1);
    for (int i = 0; i < numSamples; ++i) {
        float xi = x.front() + i * dx;
        int j = n - 2;
        while (j >= 0 && xi < x[j]) {
            --j;
        }
        float diff = xi - x[j];
        interpolatedY[i] = a[j] + b[j] * diff + c[j] * diff * diff + d[j] * diff * diff * diff;
    }

    return interpolatedY;
}

std::pair<Mesh*, std::vector<float>> objects2D::CreateField(
    float width,
    float height,
    glm::vec3 origin,
    std::vector<float> fieldHeightMap) {

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    float amplitude1 = 0.9f, frequency1 = 1.0f;
    float amplitude2 = 0.6f, frequency2 = 2.0f;
    float amplitude3 = 2.1f, frequency3 = 0.5f;

    int numSamples = 200;
    float dx = width / numSamples;

    glm::vec3 color = glm::vec3(0.5f, 0.32f, 0.2f);
    if (fieldHeightMap.empty()) {
        std::vector<float> x(numSamples + 1);
        std::vector<float> y(numSamples + 1);

        for (int i = 0; i <= numSamples; i++) {
            x[i] = i * dx;
            y[i] = amplitude1 * sin(frequency1 * x[i]) +
                amplitude2 * sin(frequency2 * x[i]) +
                amplitude3 * sin(frequency3 * x[i]) + 7;
        }

        fieldHeightMap = CubicSplineInterpolation(x, y, numSamples * 10);

        for (int i = 0; i < fieldHeightMap.size(); i++) {
            fieldHeightMap[i] = (fieldHeightMap[i] + 2) * height / 4;
        }

        SmoothHeightMap(fieldHeightMap);
    }

    for (int i = 0; i < fieldHeightMap.size(); i++) {
        vertices.push_back(VertexFormat(glm::vec3(i * dx / 10, fieldHeightMap[i], 0), color));
        vertices.push_back(VertexFormat(glm::vec3(i * dx / 10, 0, 0), color));
    }

    for (int i = 0; i < fieldHeightMap.size() - 1; i++) {
        indices.push_back(i * 2);
        indices.push_back(i * 2 + 1);
        indices.push_back((i + 1) * 2);

        indices.push_back(i * 2 + 1);
        indices.push_back((i + 1) * 2 + 1);
        indices.push_back((i + 1) * 2);
    }

    Mesh* field = new Mesh("field");
    field->SetDrawMode(GL_TRIANGLES);
    field->InitFromData(vertices, indices);

    return { field, fieldHeightMap };
}

Mesh* objects2D::CreateTrapezoid(glm::string name,float width, float height, float topWidth, glm::vec3 color) {
    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(-width / 2, 0, 0), color),
        VertexFormat(glm::vec3(width / 2, 0, 0), color),
        VertexFormat(glm::vec3(topWidth / 2, height, 0), color),
        VertexFormat(glm::vec3(-topWidth / 2, height, 0), color)
    };

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2,3,0
	};

	Mesh* trapezoid = new Mesh(name);
	trapezoid->InitFromData(vertices, indices);

	return trapezoid;
}

Mesh* objects2D::CreateSemicircle(glm::string name,float radius, int segments, glm::vec3 color) {
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));

    for (int i = 0; i <= segments; i++) {
        float theta = glm::pi<float>() * (float)i / (float)segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    std::vector<unsigned int> indices;
    for (int i = 1; i <= segments; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    Mesh* semicircle = new Mesh(name);
    semicircle->InitFromData(vertices, indices);
    return semicircle;
}

Mesh* objects2D::CreateRectangle(const std::string& name, float width, float height, glm::vec3 color) {
    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(-width / 2, 0, 0), color),
        VertexFormat(glm::vec3(width / 2, 0, 0), color),
        VertexFormat(glm::vec3(width / 2, height, 0), color),
        VertexFormat(glm::vec3(-width / 2, height, 0), color)
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    Mesh* rectangle = new Mesh(name);
    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

void objects2D::SmoothHeightMap(std::vector<float>& heightMap) {
	std::vector<float> smoothedHeightMap = heightMap;
	for (int i = 1; i < heightMap.size() - 1; i++) {
		smoothedHeightMap[i] = (heightMap[i - 1] + heightMap[i] + heightMap[i + 1]) / 3;
	}
	heightMap = smoothedHeightMap;
}

Mesh* objects2D::CreateCircle(const std::string& name, float radius, int segments, glm::vec3 color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));

    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * glm::pi<float>() * float(i) / float(segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    for (int i = 1; i <= segments; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    Mesh* circle = new Mesh(name);
    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* objects2D::CreateLine(const std::string& name, const glm::vec3& color) {
    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(0, 0, 0), color),
        VertexFormat(glm::vec3(1, 0, 0), color)
    };

    std::vector<unsigned int> indices = { 0, 1 };

    Mesh* line = new Mesh(name);
    line->InitFromData(vertices, indices);
    return line;
}

Mesh* objects2D::CreateEllipse(const std::string& name, float radiusX, float radiusY, glm::vec3 color) {
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    int numTriangles = 36;
    float angleStep = 2 * M_PI / numTriangles;

    for (int i = 0; i <= numTriangles; ++i) {
        float angle = i * angleStep;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);
        vertices.emplace_back(glm::vec3(x, y, 0), color);
        indices.push_back(i);
    }

    Mesh* ellipse = new Mesh(name);
    ellipse->InitFromData(vertices, indices);
    ellipse->SetDrawMode(GL_TRIANGLE_FAN);
    return ellipse;
}

Mesh* objects2D::CreateDiamond(std::string name, float width, float height, glm::vec3 color) {
    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(0, height / 2, 0), color),
        VertexFormat(glm::vec3(width / 2, 0, 0), color),
        VertexFormat(glm::vec3(0, -height / 2, 0), color),
        VertexFormat(glm::vec3(-width / 2, 0, 0), color)
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0 
    };

    Mesh* diamond = new Mesh(name);
    diamond->InitFromData(vertices, indices);
    return diamond;
}
