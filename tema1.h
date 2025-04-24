#pragma once

#include "components/simple_scene.h"
#include <vector>
#include <glm/glm.hpp>

namespace m1
{
    struct ImpactPoint {
        int index;
        int radius;
    };

    class Bullet {
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        float radius;
        int tankId;

        Bullet(glm::vec2 pos, glm::vec2 vel, float r, int id)
            : position(pos), velocity(vel), radius(r), tankId(id) {}
    };

    enum ShootingMode {
        SINGLE_SHOT,
        AUTOMATIC
    };

    struct FireParticle {
        glm::vec2 position;
        glm::vec2 velocity;
        float lifetime;
        glm::vec3 color;
    };


    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        std::vector<Bullet> tank1Bullets;
        std::vector<Bullet> tank2Bullets;
        void Init() override;
        std::vector<float> fieldHeightMap;
        float tankX = 100.0f;
        float tankY = 100.0f;
        float tankSpeed = 0;
        float tank2X = 100.0f;
        float tank2Y = 100.0f;
        float tank2Angle = 0.0f;
        float trajectoryAngle = 1.57f;
        float trajectoryAngle2 = 1.57f;
        glm::mat3 baseTransform = glm::mat3(1);
        const float gravity = 250.f;
        float turretEndX = 0.0f;
        float turretEndY = 0.0f;
        float turret2EndX = 0.0f;
        float turret2EndY = 0.0f;
        bool smoothingInProgress = false;
        int smoothingRadius;
        int smoothingIndex;
        std::vector<float> targetHeightMap;
        float smoothingTimer;
        std::vector<ImpactPoint> impactPoints;
        float trajectoryStartX;
        float trajectoryStartY;
        float trajectoryStartX2;
        float trajectoryStartY2;
        glm::vec2 tank1Recoil;
        glm::vec2 tank2Recoil;
        float recoilDuration;
        int tank2HitCounter = 0;
        int tank1HitCounter = 0;
        float initialHealthBarWidth = 30.0f;
        float rayLength = 10.0f;
        float rayThickness = 0.5f;
        std::vector<glm::vec2> cloudPositions;
        std::vector<glm::vec3> cloudColors;
        std::vector<std::vector<glm::vec2>> cloudOffsets;
        float cloudSpeed;
        std::vector<float> cloudSizes;
        float cameraShakeIntensity = 0.0f;
        float cameraShakeDuration = 0.0f;
        glm::vec3 cameraShakeOffset = glm::vec3(0.7f);
        bool isFiring = false;
        glm::vec3 tankPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        ShootingMode currentMode = SINGLE_SHOT;
        ShootingMode currentMode2 = SINGLE_SHOT;
        float timeSinceLastShot = 0.0f;
        float fireRate = 0.25f;
        const float smoothingDuration = 3.0f;
        std::vector<FireParticle> fireParticles;
        glm::vec2 cupPosition;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderBullet(const Bullet& bullet);
        void CreateCrater(std::vector<float>& heightMap, float impactX, float craterRadius, float dx);
        void UpdateFieldMesh();
        void SmoothCrater(std::vector<float>& heightMap);
        float RenderTrajectory(float startX, float startY, float turretAngle, float velocity, float gravity);
        void RenderLine(float x1, float y1, float x2, float y2, glm::vec3 color);
        void RenderSunWithRays();
        void RenderClouds();
        void CreateClouds();
        bool scaling;
        bool translating;
        void SpawnFire(float deltaTime, glm::vec2 tankPosition);
        void UpdateFire(float deltaTime);
        void RenderFire();
        Mesh* CreateCup(const std::string& name, const glm::vec3& color);
        void RenderCup(const glm::vec2& position);
        Mesh* CreateCupRays(const glm::vec3& color1, const glm::vec3& color2, const glm::vec3& color3);
        void RenderCupRays(const glm::vec2& position, float angle);

    protected:
        float cx = 0.0f, cy = 0.0f;
        glm::mat3 modelMatrix;
        float translateX = 0.0f, translateY = 0.0f;
        float scaleX = 1.0f, scaleY = 1.0f;
        float angularStep = 0.0f;
        float fieldWidth = 0.0f, fieldHeight = 0.0f;
        float angle = 0.0f;
        float turretHeightOffset = 0.0f;
        float turretAngle1 = 1.57f;
        float turretAngle2 = 1.57f;
    };
}
