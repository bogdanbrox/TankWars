#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>

#include "lab_m1/tema1/transforms2D.h"
#include "lab_m1/tema1/objects2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

Mesh* Tema1::CreateCup(const std::string& name, const glm::vec3& color) {
    Mesh* base = objects2D::CreateRectangle("cupBase", 160, 25, glm::vec3(0.4f, 0.26f, 0.13f));
    AddMeshToList(base);
    
    Mesh* upperBowl = objects2D::CreateEllipse("cupUpperBowl2", 80.0f, 20.0f, glm::vec3(0.72f, 0.52f, 0.043f));
    AddMeshToList(upperBowl);

    Mesh* lowerBowl = objects2D::CreateEllipse("cupLowerBowl1", 80.0f, 20.0f, color);
    AddMeshToList(lowerBowl);

    Mesh* stem = objects2D::CreateRectangle("cupStem1", 30, 40, color);
    AddMeshToList(stem);
    
    stem = objects2D::CreateRectangle("cupStem2", 160, 130, color);
    AddMeshToList(stem);

    stem = objects2D::CreateRectangle("cupStem3", 70, 10, color);
    AddMeshToList(stem);
    return base;
}

Mesh* Tema1::CreateCupRays(const glm::vec3& color1, const glm::vec3& color2, const glm::vec3& color3) {
    Mesh* ray1 = objects2D::CreateRectangle("cupRay1", 15, 180, color1);
    AddMeshToList(ray1);

    Mesh* ray2 = objects2D::CreateRectangle("cupRay2", 15, 180, color2);
    AddMeshToList(ray2);

    Mesh* ray3 = objects2D::CreateRectangle("cupRay3", 15, 180, color3);
    AddMeshToList(ray3);

    return ray1;
}

void Tema1::RenderCupRays(const glm::vec2& position, float angle) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle);
    RenderMesh2D(meshes["cupRay1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 0.523f);
    RenderMesh2D(meshes["cupRay2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 1.046f);
    RenderMesh2D(meshes["cupRay3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 1.569f);
    RenderMesh2D(meshes["cupRay1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 2.09f);
    RenderMesh2D(meshes["cupRay2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 2.615);
    RenderMesh2D(meshes["cupRay3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 3.138f);
    RenderMesh2D(meshes["cupRay1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 3.661f);
    RenderMesh2D(meshes["cupRay2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 4.184f);
    RenderMesh2D(meshes["cupRay3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 4.707f);
    RenderMesh2D(meshes["cupRay1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 5.23f);
    RenderMesh2D(meshes["cupRay2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    modelMatrix *= transforms2D::Rotate(angle + 5.753f);
    RenderMesh2D(meshes["cupRay3"], shaders["VertexColor"], modelMatrix);

}


void Tema1::SpawnFire(float deltaTime, glm::vec2 tankPosition) {
    static float fireTimer = 0.0f;
    fireTimer += deltaTime;
    if (fireTimer >= 0.05f) {
        fireTimer = 0.0f;

        FireParticle particle;
        float randomOffsetX = (rand() % 10 - 5);
        float randomOffsetY = (rand() % 5);
        particle.position = glm::vec2(tankPosition.x + randomOffsetX, tankPosition.y + randomOffsetY);

        particle.velocity = glm::vec2(rand() % 20 - 10, rand() % 20 + 30);

        particle.lifetime = 1.5f;

        particle.color = glm::vec3(1.0f, (rand() % 50 + 50) / 100.0f, 0.0f);

        fireParticles.push_back(particle);
    }
}

void Tema1::UpdateFire(float deltaTime) {
    for (size_t i = 0; i < fireParticles.size(); ++i) {
        fireParticles[i].position += fireParticles[i].velocity * deltaTime;
        fireParticles[i].lifetime -= deltaTime;
        if (fireParticles[i].lifetime <= 0) {
            fireParticles.erase(fireParticles.begin() + i);
            --i;
        }
    }
}

void Tema1::RenderFire() {
    for (const auto& particle : fireParticles) {
        Mesh* fireParticle = objects2D::CreateEllipse("fireParticle", 5.0f, 5.0f, particle.color);
        AddMeshToList(fireParticle);

        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= transforms2D::Translate(particle.position.x, particle.position.y);
        RenderMesh2D(meshes["fireParticle"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderSunWithRays() {
    Mesh* sun = objects2D::CreateCircle("sun", 30, 36, glm::vec3(1.0f, 1.0f, 0.0f));
    AddMeshToList(sun);

    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(500, 500);
    RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);

    float sunX = 500, sunY = 500;
    float rayLength = 50.0f;
    float rayThickness = 4.0f;
    int numRays = 10;
    float angleStep = 2 * M_PI / numRays;

    for (int i = 0; i < numRays; ++i) {

        float angle = i * angleStep;

        float dx = rayLength * cos(angle);
        float dy = rayLength * sin(angle);

        Mesh* ray = objects2D::CreateRectangle("ray" + std::to_string(i), rayThickness, rayLength, glm::vec3(1.0f, 1.0f, 0.0f));
        AddMeshToList(ray);

        glm::mat3 rayModelMatrix = glm::mat3(1);
        rayModelMatrix *= transforms2D::Translate(sunX, sunY);
        rayModelMatrix *= transforms2D::Rotate(angle);
        rayModelMatrix *= transforms2D::Translate(-rayThickness / 2, 10);

        RenderMesh2D(meshes["ray" + std::to_string(i)], shaders["VertexColor"], rayModelMatrix);
    }
}

float Tema1::RenderTrajectory(float startX, float startY, float turretAngle, float velocity, float gravity) {
    std::vector<glm::vec2> trajectoryPoints;
    float timeStep = 0.01f;
    float maxTime = 10.0f;
    float heightScale = 1.01f;

    trajectoryPoints.push_back(glm::vec2(startX, startY));

    for (float t = 0; t < maxTime; t += timeStep) {
        float x = velocity * t * cos(turretAngle);
        float y = (velocity * t * sin(turretAngle) - 0.5f * gravity * t * t) * heightScale;

        float posX = startX + x;
        float posY = startY + y;

        if (posX >= 0 && posX < fieldWidth) {
            int fieldIndex = static_cast<int>(posX / fieldWidth * fieldHeightMap.size());
            if (posY <= fieldHeightMap[fieldIndex]) {
                break;
            }
        }

        trajectoryPoints.push_back(glm::vec2(posX, posY));
    }

    glLineWidth(3.0f);
    for (size_t i = 1; i < trajectoryPoints.size(); ++i) {
        glm::vec2 p1 = trajectoryPoints[i - 1];
        glm::vec2 p2 = trajectoryPoints[i];
        RenderLine(p1.x, p1.y, p2.x, p2.y, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    glLineWidth(1.0f);

    if (trajectoryPoints.size() >= 2) {
        glm::vec2 direction = trajectoryPoints[1] - trajectoryPoints[0];
        return atan2(direction.y, direction.x);
    }

    return turretAngle;
}

void Tema1::RenderLine(float x1, float y1, float x2, float y2, glm::vec3 color) {
    glm::mat3 modelMatrix = glm::mat3(1);
    std::vector<VertexFormat> lineVertices = {
        VertexFormat(glm::vec3(x1, y1, 0), color),
        VertexFormat(glm::vec3(x2, y2, 0), color)
    };
    std::vector<unsigned int> indices = { 0, 1 };

    Mesh* line = new Mesh("line");
    line->InitFromData(lineVertices, indices);
    line->SetDrawMode(GL_LINES);
    RenderMesh2D(line, shaders["VertexColor"], modelMatrix);
}

void Tema1::UpdateFieldMesh() {
    auto updatedFieldResult = objects2D::CreateField(fieldWidth, fieldHeight, glm::vec3(0, 0, 0), fieldHeightMap);
    Mesh* updatedField = updatedFieldResult.first;
    fieldHeightMap = updatedFieldResult.second;

    meshes["field"] = updatedField;
}

void Tema1::CreateCrater(std::vector<float>& heightMap, float impactX, float craterRadius, float dx) {
    int impactIndex = static_cast<int>(impactX / dx);
    int numSamples = heightMap.size();
    int startIndex = std::max(0, impactIndex - static_cast<int>(craterRadius / dx));
    int endIndex = std::min(numSamples - 1, impactIndex + static_cast<int>(craterRadius / dx));

    float impactHeight = heightMap[impactIndex];
    for (int i = startIndex; i <= endIndex; ++i) {
        float distanceX = std::abs(i - impactIndex) * dx;

        if (distanceX <= craterRadius) {
            float depthReduction = sqrt(craterRadius * craterRadius - distanceX * distanceX);
            float newHeight = impactHeight - depthReduction;

            heightMap[i] = std::min(heightMap[i], newHeight);
        }
    }
    impactPoints.push_back({ impactIndex, static_cast<int>(craterRadius + 25 / dx) });

    UpdateFieldMesh();
}

void Tema1::CreateClouds() {

    cloudOffsets = {
        { glm::vec2(0.0f, 0.0f), glm::vec2(40.0f, 15.0f), glm::vec2(-40.0f, 15.0f), glm::vec2(20.0f, -10.0f) },
        { glm::vec2(0.0f, 0.0f), glm::vec2(30.0f, 10.0f), glm::vec2(-30.0f, 10.0f) },
        { glm::vec2(0.0f, 0.0f), glm::vec2(40.0f, 15.0f), glm::vec2(-40.0f, 15.0f), glm::vec2(20.0f, -10.0f) },
        { glm::vec2(0.0f, 0.0f), glm::vec2(25.0f, 5.0f), glm::vec2(-25.0f, 5.0f), glm::vec2(15.0f, -5.0f), glm::vec2(-15.0f, -5.0f) },
        { glm::vec2(0.0f, 0.0f), glm::vec2(35.0f, 10.0f), glm::vec2(-35.0f, 10.0f), glm::vec2(20.0f, -10.0f), glm::vec2(-20.0f, -10.0f) },
        { glm::vec2(0.0f, 0.0f), glm::vec2(35.0f, 10.0f), glm::vec2(-35.0f, 10.0f), glm::vec2(20.0f, -10.0f), glm::vec2(-20.0f, -10.0f) },
        { glm::vec2(0.0f, 0.0f), glm::vec2(30.0f, 10.0f), glm::vec2(-30.0f, 10.0f) },
        { glm::vec2(0.0f, 0.0f), glm::vec2(35.0f, 10.0f), glm::vec2(-35.0f, 10.0f), glm::vec2(20.0f, -10.0f), glm::vec2(-20.0f, -10.0f) },
        { glm::vec2(0.0f, 0.0f), glm::vec2(30.0f, 10.0f), glm::vec2(-30.0f, 10.0f), glm::vec2(15.0f, -10.0f), glm::vec2(-15.0f, -10.0f), glm::vec2(0.0f, -20.0f) }
    };

    cloudPositions.clear();
    for (int i = 0; i < 30; ++i) {
        cloudPositions.push_back(glm::vec2(rand() % 2000, rand() % 300 + 400));
    }
}

void Tema1::RenderClouds() {
    for (size_t i = 0; i < cloudPositions.size(); ++i) {

        glm::vec3 cloudColor = glm::vec3(0.9f, 0.9f, 0.9f);

        for (size_t j = 0; j < cloudOffsets[i % cloudOffsets.size()].size(); ++j) {
            glm::vec2 offset = cloudOffsets[i % cloudOffsets.size()][j];

            Mesh* cloudPart = objects2D::CreateEllipse("cloudPart" + std::to_string(i) + "_" + std::to_string(j),
                40, 30, cloudColor);
            AddMeshToList(cloudPart);

            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transforms2D::Translate(cloudPositions[i].x + offset.x, cloudPositions[i].y + offset.y);

            RenderMesh2D(meshes["cloudPart" + std::to_string(i) + "_" + std::to_string(j)], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Tema1::SmoothCrater(std::vector<float>& heightMap) {
    if (impactPoints.empty()) return;

    float smoothingFactor = 0.7f;
    std::vector<float> newHeightMap = heightMap;

    for (const auto& impact : impactPoints) {
        int startIndex = std::max(0, impact.index - impact.radius);
        int endIndex = std::min(static_cast<int>(heightMap.size()) - 1, impact.index + impact.radius);

        for (int i = startIndex; i <= endIndex; ++i) {
            int leftNeighbor = std::max(0, i - 1);
            int rightNeighbor = std::min(static_cast<int>(heightMap.size()) - 1, i + 1);

            newHeightMap[i] = heightMap[i] * (1.0f - smoothingFactor) +
                (heightMap[leftNeighbor] + heightMap[rightNeighbor]) * 0.5f * smoothingFactor;
        }
    }

    heightMap = newHeightMap;
    UpdateFieldMesh();
}

void Tema1::RenderBullet(const Bullet& bullet) {
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(bullet.position.x, bullet.position.y);
    modelMatrix *= transforms2D::Scale(bullet.radius, bullet.radius);
    RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderCup(const glm::vec2& position) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 142);
    RenderMesh2D(meshes["cupStem3"], shaders["VertexColor"], modelMatrix);

    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 150);
    RenderMesh2D(meshes["cupBase"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 130);
    RenderMesh2D(meshes["cupStem1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 80);
    RenderMesh2D(meshes["cupLowerBowl1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y + 50);
    RenderMesh2D(meshes["cupUpperBowl2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transforms2D::Translate(position.x + 110, position.y - 80);
    RenderMesh2D(meshes["cupStem2"], shaders["VertexColor"], modelMatrix);

    CreateCupRays(glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}



void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    CreateClouds();

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    fieldWidth = 2 * (float)(resolution.x);
    fieldHeight = 100.0f;

    cupPosition = glm::vec2(500.0f, 500.0f);

    auto fieldResult = objects2D::CreateField(fieldWidth, fieldHeight, corner);
    Mesh* field = fieldResult.first;
    fieldHeightMap = fieldResult.second;

    AddMeshToList(field);

    Mesh* trapezoid = objects2D::CreateTrapezoid("t1", 28, 6, 35, glm::vec3(0.21f, 0.27f, 0.31f));
    AddMeshToList(trapezoid);

    trapezoid = objects2D::CreateTrapezoid("t2", 42, 9, 33, glm::vec3(0.29f, 0.33f, 0.13f));
    AddMeshToList(trapezoid);

    Mesh* semicircle = objects2D::CreateSemicircle("c1", 8, 30, glm::vec3(0.29f, 0.33f, 0.13f));
    AddMeshToList(semicircle);

    Mesh* rectangle = objects2D::CreateRectangle("r1", 24, 2, glm::vec3(0, 0, 0));
    AddMeshToList(rectangle);

    tankSpeed = 100;

    trapezoid = objects2D::CreateTrapezoid("t3", 28, 6, 35, glm::vec3(0.2f, 0.2f, 0.2f));
    AddMeshToList(trapezoid);
    tank2X = resolution.x - 100;

    trapezoid = objects2D::CreateTrapezoid("t4", 42, 9, 33, glm::vec3(0.3f, 0.3f, 0.3f));
    AddMeshToList(trapezoid);

    semicircle = objects2D::CreateSemicircle("c2", 8, 30, glm::vec3(0.3f, 0.3f, 0.3f));
    AddMeshToList(semicircle);

    rectangle = objects2D::CreateRectangle("r2", 24, 2, glm::vec3(0.5f, 0.35f, 0.05f));
    AddMeshToList(rectangle);

    Mesh* circle = objects2D::CreateCircle("bullet", 0.7f, 36, glm::vec3(0.0f, 0.0f, 0.0f));
    AddMeshToList(circle);

    Mesh* healthBar = objects2D::CreateRectangle("healthBar", 2, 6, glm::vec3(0.0f, 0.5f, 0.0f));
    AddMeshToList(healthBar);

    Mesh* sun = objects2D::CreateCircle("sun", 30, 36, glm::vec3(1.0f, 1.0f, 0.0f));
    AddMeshToList(sun);

    trapezoid = objects2D::CreateTrapezoid("t5", 28, 6, 35, glm::vec3(0.0f, 0.0f, 0.0f));
    AddMeshToList(trapezoid);

    trapezoid = objects2D::CreateTrapezoid("t6", 42, 9, 33, glm::vec3(0.0f, 0.0f, 0.0f));
    AddMeshToList(trapezoid);

    semicircle = objects2D::CreateSemicircle("c3", 8, 30, glm::vec3(0.0f, 0.0f, 0.0f));
    AddMeshToList(semicircle);

    rectangle = objects2D::CreateRectangle("r3", 24, 2, glm::vec3(0.0f, 0.0f, 0.0f));
    AddMeshToList(rectangle);

    CreateCup("cup", glm::vec3(1.0f, 0.843f, 0.0f));
}

void Tema1::FrameStart()
{
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["field"], shaders["VertexColor"], modelMatrix);

    float tankFrontX = tankX + 15;
    float tankBackX = tankX - 15;

    float fieldSegmentWidth = fieldHeightMap.size() ? fieldWidth / fieldHeightMap.size() : 1;

    int frontIndex = static_cast<int>(tankFrontX / fieldSegmentWidth);
    int backIndex = static_cast<int>(tankBackX / fieldSegmentWidth);

    float tankFrontY = (frontIndex >= 0 && frontIndex < fieldHeightMap.size()) ? fieldHeightMap[frontIndex] : 0;
    float tankBackY = (backIndex >= 0 && backIndex < fieldHeightMap.size()) ? fieldHeightMap[backIndex] : 0;

    float targetAngle = atan2(tankFrontY - tankBackY, tankFrontX - tankBackX);

    float heightDifference = abs(tankFrontY - tankBackY);

    float baseSmoothingFactor = 1.0f;
    float maxSmoothingFactor = 1.0f;

    float smoothingFactor = baseSmoothingFactor + (maxSmoothingFactor - baseSmoothingFactor) * pow((heightDifference / fieldHeight), 2);

    angle = lerp(angle, targetAngle, smoothingFactor);

    float tankCenterX = tankX;
    float tankCenterY = (tankFrontY + tankBackY) / 2;

    float submersionOffset = 5.0f;
    tankCenterY -= submersionOffset;

    glm::mat3 baseTransform = glm::mat3(1);
    baseTransform *= transforms2D::Translate(tankCenterX, tankCenterY);
    baseTransform *= transforms2D::Rotate(angle);

    if (tank1HitCounter < 5) {

        modelMatrix = baseTransform;
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["t1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = baseTransform;
        modelMatrix *= transforms2D::Translate(0, 6 * 2);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["t2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = baseTransform;
        modelMatrix *= transforms2D::Translate(0, 6 * 2 + 9 * 2);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["c1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = baseTransform;
        modelMatrix *= transforms2D::Translate(18, 6 * 2 + 9 * 2);
        modelMatrix *= transforms2D::Translate(-16, 0);
        modelMatrix *= transforms2D::Rotate(turretAngle1 - angle);
        modelMatrix *= transforms2D::Translate(16, 0);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["r1"], shaders["VertexColor"], modelMatrix);

        turretEndX = tankCenterX + 20 * cos(turretAngle1);
        turretEndY = tankCenterY + 40 * sin(turretAngle1);

        glm::vec3 trajectoryStartWorld = modelMatrix * glm::vec3(12, 0.8f, 1);
        trajectoryStartX = trajectoryStartWorld.x;
        trajectoryStartY = trajectoryStartWorld.y;

        float healthPercentage = 1.0f - (tank1HitCounter / 5.0f);
        glm::vec3 healthColor = glm::vec3(1.0f - healthPercentage, healthPercentage, 0.0f);
        float healthBarWidth = initialHealthBarWidth * healthPercentage;
        glm::mat3 healthBarMatrix = glm::mat3(1);
        healthBarMatrix *= transforms2D::Translate(tankX, tankCenterY + 80);
        healthBarMatrix *= transforms2D::Scale(healthBarWidth, 2);
        RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], healthBarMatrix);
    }
    else {

        modelMatrix = baseTransform;
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["t5"], shaders["VertexColor"], modelMatrix);

        modelMatrix = baseTransform;
        modelMatrix *= transforms2D::Translate(0, 6 * 2);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["t6"], shaders["VertexColor"], modelMatrix);

        modelMatrix = baseTransform;
        modelMatrix *= transforms2D::Translate(0, 6 * 2 + 9 * 2);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["c3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = baseTransform;
        modelMatrix *= transforms2D::Translate(18, 6 * 2 + 9 * 2);
        modelMatrix *= transforms2D::Translate(-16, 0);
        modelMatrix *= transforms2D::Rotate(turretAngle1 - angle);
        modelMatrix *= transforms2D::Translate(16, 0);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["r3"], shaders["VertexColor"], modelMatrix);
        SpawnFire(deltaTimeSeconds, glm::vec2(tankX, tankCenterY));
        UpdateFire(deltaTimeSeconds);
        RenderFire();
        RenderCup(cupPosition);
        RenderCupRays(glm::vec2(500.0f, 600.0f), 0.0f);
    }

    float tank2FrontX = tank2X + 15;
    float tank2BackX = tank2X - 15;

    int tank2FrontIndex = static_cast<int>(tank2FrontX / fieldSegmentWidth);
    int tank2BackIndex = static_cast<int>(tank2BackX / fieldSegmentWidth);

    float tank2FrontY = (tank2FrontIndex >= 0 && tank2FrontIndex < fieldHeightMap.size()) ? fieldHeightMap[tank2FrontIndex] : 0;
    float tank2BackY = (tank2BackIndex >= 0 && tank2BackIndex < fieldHeightMap.size()) ? fieldHeightMap[tank2BackIndex] : 0;

    float tank2TargetAngle = atan2(tank2FrontY - tank2BackY, tank2FrontX - tank2BackX);

    float tank2HeightDifference = abs(tank2FrontY - tank2BackY);

    float tank2SmoothingFactor = baseSmoothingFactor + (maxSmoothingFactor - baseSmoothingFactor) * pow((tank2HeightDifference / fieldHeight), 2);

    tank2Angle = lerp(tank2Angle, tank2TargetAngle, tank2SmoothingFactor);

    float tank2CenterX = tank2X;
    float tank2CenterY = (tank2FrontY + tank2BackY) / 2;

    tank2CenterY -= submersionOffset;

    glm::mat3 tank2BaseTransform = glm::mat3(1);
    tank2BaseTransform *= transforms2D::Translate(tank2CenterX, tank2CenterY);
    tank2BaseTransform *= transforms2D::Rotate(tank2Angle);

    if (tank2HitCounter < 5) {

        modelMatrix = tank2BaseTransform;
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["t3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tank2BaseTransform;
        modelMatrix *= transforms2D::Translate(0, 6 * 2);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["t4"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tank2BaseTransform;
        modelMatrix *= transforms2D::Translate(0, 6 * 2 + 9 * 2);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["c2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tank2BaseTransform;
        modelMatrix *= transforms2D::Translate(18, 6 * 2 + 9 * 2);
        modelMatrix *= transforms2D::Translate(-16, 0);
        modelMatrix *= transforms2D::Rotate(turretAngle2 - tank2Angle);
        modelMatrix *= transforms2D::Translate(16, 0);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["r2"], shaders["VertexColor"], modelMatrix);

        turret2EndX = tank2CenterX + 20 * cos(turretAngle2);
        turret2EndY = tank2CenterY + 40 * sin(turretAngle2);

        glm::vec3 trajectoryStartWorld2 = modelMatrix * glm::vec3(12, 0.8f, 1);
        trajectoryStartX2 = trajectoryStartWorld2.x;
        trajectoryStartY2 = trajectoryStartWorld2.y;
        RenderTrajectory(trajectoryStartX2, trajectoryStartY2, trajectoryAngle2, 350.0f, gravity);


        float healthBarWidth = initialHealthBarWidth * (1.0f - (tank2HitCounter / 5.0f));
        glm::mat3 healthBarMatrix = glm::mat3(1);
        healthBarMatrix *= transforms2D::Translate(tank2X, tank2CenterY + 80);
        healthBarMatrix *= transforms2D::Scale(healthBarWidth, 2);
        RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], healthBarMatrix);
    }
    else {

        modelMatrix = tank2BaseTransform;
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["t5"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tank2BaseTransform;
        modelMatrix *= transforms2D::Translate(0, 6 * 2);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["t6"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tank2BaseTransform;
        modelMatrix *= transforms2D::Translate(0, 6 * 2 + 9 * 2);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["c3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tank2BaseTransform;
        modelMatrix *= transforms2D::Translate(18, 6 * 2 + 9 * 2);
        modelMatrix *= transforms2D::Translate(-16, 0);
        modelMatrix *= transforms2D::Rotate(turretAngle2 - tank2Angle);
        modelMatrix *= transforms2D::Translate(16, 0);
        modelMatrix *= transforms2D::Scale(2, 2);
        RenderMesh2D(meshes["r3"], shaders["VertexColor"], modelMatrix);
        SpawnFire(deltaTimeSeconds, glm::vec2(tank2X, tank2CenterY));
        UpdateFire(deltaTimeSeconds);
        RenderFire();
        RenderCup(cupPosition);
        RenderCupRays(glm::vec2(500.0f, 600.0f), 0.0f);
    }

    if (tank1HitCounter < 5) {

        RenderTrajectory(trajectoryStartX, trajectoryStartY, trajectoryAngle, 350.0f, gravity);
    }

    for (auto it = tank1Bullets.begin(); it != tank1Bullets.end(); ) {
        it->position.x += it->velocity.x * deltaTimeSeconds;
        it->position.y += it->velocity.y * deltaTimeSeconds;
        it->velocity.y -= gravity * deltaTimeSeconds;

        int bulletIndex = static_cast<int>(it->position.x / fieldSegmentWidth);
        if (bulletIndex >= 0 && bulletIndex < fieldHeightMap.size()) {
            float groundHeight = fieldHeightMap[bulletIndex];
            if (it->position.y <= groundHeight) {
                CreateCrater(fieldHeightMap, it->position.x, 50.0f, fieldSegmentWidth);
                smoothingInProgress = true;
                if (smoothingInProgress) {
                    smoothingTimer += deltaTimeSeconds;
                    if (smoothingTimer >= smoothingDuration) {
                        smoothingInProgress = false;
                    }
                }

                cameraShakeDuration = 0.5f;
                cameraShakeIntensity = 1.0f;

                it = tank1Bullets.erase(it);
                continue;
            }
        }

        if (tank2HitCounter < 5 && it->tankId != 2) {
            float tank2LeftX = tank2X - 15;
            float tank2RightX = tank2X + 15;

            if (it->position.x >= tank2LeftX - 20 && it->position.x <= tank2RightX + 20) {
                float tank2CenterY = (tank2FrontY + tank2BackY) / 2;

                if (it->position.y >= tank2CenterY - 30 && it->position.y <= tank2CenterY + 30 && tank2HitCounter == 4) {
                    cameraShakeDuration = 0.5f;
                    cameraShakeIntensity = 1.0f;
                    tank2HitCounter++;
                    it = tank1Bullets.erase(it);
                    if (tank2HitCounter >= 5) {
                        break;
                    }
                    continue;
                }
                else if (it->position.y >= tank2CenterY - 30 && it->position.y <= tank2CenterY + 30) {
                    tank2HitCounter++;
                    it = tank1Bullets.erase(it);
                    if (tank2HitCounter >= 5) {
                        break;
                    }
                    continue;
                }
            }
        }

        RenderBullet(*it);
        ++it;
    }

    for (auto it = tank2Bullets.begin(); it != tank2Bullets.end(); ) {
        it->position.x += it->velocity.x * deltaTimeSeconds;
        it->position.y += it->velocity.y * deltaTimeSeconds;
        it->velocity.y -= gravity * deltaTimeSeconds;

        int bulletIndex = static_cast<int>(it->position.x / fieldSegmentWidth);
        if (bulletIndex >= 0 && bulletIndex < fieldHeightMap.size()) {
            float groundHeight = fieldHeightMap[bulletIndex];
            if (it->position.y <= groundHeight) {
                CreateCrater(fieldHeightMap, it->position.x, 50.0f, fieldSegmentWidth);
                smoothingInProgress = true;
                if (smoothingInProgress) {
                    smoothingTimer += deltaTimeSeconds;
                    if (smoothingTimer >= smoothingDuration) {
                        smoothingInProgress = false;
                    }
                }
                cameraShakeDuration = 0.5f;
                cameraShakeIntensity = 2.0f;

                it = tank2Bullets.erase(it);
                continue;
            }
        }

        if (tank1HitCounter < 5 && it->tankId != 1) {
            float tank1LeftX = tankX - 15;
            float tank1RightX = tankX + 15;

            if (it->position.x >= tank1LeftX - 20 && it->position.x <= tank1RightX + 20) {
                float tank1CenterY = (tankFrontY + tankBackY) / 2;

                if (it->position.y >= tank1CenterY - 30 && it->position.y <= tank1CenterY + 30 && tank1HitCounter == 4) {
                    cameraShakeDuration = 0.5f;
                    cameraShakeIntensity = 2.0f;
                    tank1HitCounter++;
                    it = tank2Bullets.erase(it);
                    if (tank1HitCounter >= 5) {
                        break;
                    }
                    continue;
                }
                else if (it->position.y >= tank1CenterY - 30 && it->position.y <= tank1CenterY + 30) {
                    tank1HitCounter++;
                    it = tank2Bullets.erase(it);
                    if (tank1HitCounter >= 5) {
                        break;
                    }
                    continue;
                }
            }
        }

        RenderBullet(*it);
        ++it;
    }
    SmoothCrater(fieldHeightMap);
    RenderClouds();
    RenderSunWithRays();

    if (cameraShakeDuration > 0.0f) {
        cameraShakeOffset = glm::vec3(
            rand() % 5 - 2,
            rand() % 5 - 2,
            0.0f
        );

        cameraShakeDuration -= deltaTimeSeconds;
        cameraShakeIntensity = cameraShakeDuration > 0 ? cameraShakeIntensity * 0.9f : 0.0f;
    }
    else {
        cameraShakeOffset = glm::vec3(0.0f);
    }
    glm::vec3 newCameraPos = glm::vec3(0, 0, 50) + cameraShakeOffset;
    GetSceneCamera()->SetPosition(newCameraPos);
    GetSceneCamera()->Update();
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    timeSinceLastShot += deltaTime;

    if (window->KeyHold(GLFW_KEY_A) && tank1HitCounter < 5) {
        tankX -= tankSpeed * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D) && tank1HitCounter < 5) {
        tankX += tankSpeed * deltaTime;
    }

    if (tankX < 0) {
        tankX = 0;
    }

    const float maxTurretAngle = 1.57f;

    if (window->KeyHold(GLFW_KEY_S) && tank1HitCounter < 5) {
        trajectoryAngle += 1.0f * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_W) && tank1HitCounter < 5) {
        trajectoryAngle -= 1.0f * deltaTime;
    }
    trajectoryAngle = glm::clamp(trajectoryAngle, 0.0f + angle, 3.14f + angle);
    turretAngle1 = trajectoryAngle;

    if (window->KeyHold(GLFW_KEY_LEFT) && tank2HitCounter < 5) {
        tank2X -= tankSpeed * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_RIGHT) && tank2HitCounter < 5) {
        tank2X += tankSpeed * deltaTime;
    }

    if (tank2X < 0) {
        tank2X = 0;
    }

    if (window->KeyHold(GLFW_KEY_UP) && tank2HitCounter < 5) {
        trajectoryAngle2 += 1.0f * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_DOWN) && tank2HitCounter < 5) {
        trajectoryAngle2 -= 1.0f * deltaTime;
    }
    trajectoryAngle2 = glm::clamp(trajectoryAngle2, 0.0f + tank2Angle, 3.14f + tank2Angle);
    turretAngle2 = trajectoryAngle2;

    if (window->KeyHold(GLFW_KEY_SPACE) && tank1HitCounter < 5) {
        if (currentMode == AUTOMATIC && timeSinceLastShot >= fireRate) {
            const float initialVelocity = 350.0f;
            glm::vec2 bulletVelocity = glm::vec2(initialVelocity * cos(turretAngle1), initialVelocity * sin(turretAngle1));
            tank1Bullets.emplace_back(glm::vec2(trajectoryStartX, trajectoryStartY), bulletVelocity, 5.0f, 1);

            timeSinceLastShot = 0.0f;
        }
    }

    if (window->KeyHold(GLFW_KEY_ENTER) && tank2HitCounter < 5) {
        if (currentMode2 == AUTOMATIC && timeSinceLastShot >= fireRate) {
            const float initialVelocity = 350.0f;
            glm::vec2 bulletVelocity = glm::vec2(initialVelocity * cos(turretAngle2), initialVelocity * sin(turretAngle2));
            tank2Bullets.emplace_back(glm::vec2(trajectoryStartX2, trajectoryStartY2), bulletVelocity, 5.0f, 2);

            timeSinceLastShot = 0.0f;
        }
    }
}

void Tema1::OnKeyPress(int key, int mods) {
    if (tank1HitCounter < 5) {
        if (key == GLFW_KEY_SPACE) {
            if (currentMode == SINGLE_SHOT) {
                const float initialVelocity = 350.0f;
                glm::vec2 bulletVelocity = glm::vec2(initialVelocity * cos(turretAngle1), initialVelocity * sin(turretAngle1));
                tank1Bullets.emplace_back(glm::vec2(trajectoryStartX, trajectoryStartY), bulletVelocity, 5.0f, 1);
            }
        }
    }
    if (tank2HitCounter < 5) {
        if (key == GLFW_KEY_ENTER) {
            if (currentMode2 == SINGLE_SHOT) {
                const float initialVelocity = 350.0f;
                glm::vec2 bulletVelocity = glm::vec2(initialVelocity * cos(turretAngle2), initialVelocity * sin(turretAngle2));
                tank2Bullets.emplace_back(glm::vec2(trajectoryStartX2, trajectoryStartY2), bulletVelocity, 5.0f, 2);
            }
        }
    }
    if (key == GLFW_KEY_U) {
        currentMode = AUTOMATIC;
    }
    if (key == GLFW_KEY_P) {
        currentMode = SINGLE_SHOT;
    }
    if (key == GLFW_KEY_1) {
        currentMode2 = AUTOMATIC;
    }
    if (key == GLFW_KEY_2) {
        currentMode2 = SINGLE_SHOT;
    }
    if (key == GLFW_KEY_R) {
        if (tank1HitCounter == 5) {
            tank1HitCounter = 0;
        }
        if (tank2HitCounter == 5) {
            tank2HitCounter = 0;
        }
    }
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}