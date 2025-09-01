#include "AnnkoTest.h"

AnnkoTest::AnnkoTest() { Initialize(); }

void AnnkoTest::Initialize() {
    transform.position = { 120.0f, 120.0f };
    speed = 10.0f;
    radius = 40.0f;
    isAlive = true;
}

void AnnkoTest::Update() {
    input.Update();

    if (input.GetKeyTrigger(DIK_SPACE)) {
        isAlive = !isAlive;
    }

    // éÄÇÒÇ≈ÇΩÇÁÅAÇ±Ç±Ç≈ï‘ÇÈ
    if (!isAlive) {
        return;
    }

    Move();
    ClampInWindow();
}

void AnnkoTest::Draw() const {
    // éÄÇÒÇ≈ÇΩÇÁÅAÇ±Ç±Ç≈ï‘ÇÈ
    if (!isAlive) {
        return;
    }

    renderer.DrawEllipse(transform, { radius, radius }, { 0.0f, 0.0f }, 0.0f, 0xFFFFFFFF, kFillModeSolid);
}

void AnnkoTest::SetCamera(const Transform2D& camera) { renderer.SetCamera(camera); }

void AnnkoTest::Move() {

    direction = { 0.0f, 0.0f };

    if (input.GetKey(DIK_W)) {
        direction.y = 1.0f;
    }

    if (input.GetKey(DIK_S)) {
        direction.y = -1.0f;
    }

    if (input.GetKey(DIK_D)) {
        direction.x = 1.0f;
    }

    if (input.GetKey(DIK_A)) {
        direction.x = -1.0f;
    }

    velocity = Vector2::Normalize(direction) * speed;
    transform.Translate(velocity);
}

void AnnkoTest::ClampInWindow() {
    if (transform.position.x <= -640.0f + radius) {
        transform.position.x = -640.0f + radius;
    }

    if (transform.position.x >= 640.0f - radius) {
        transform.position.x = 640.0f - radius;
    }

    if (transform.position.y <= -360.0f + radius) {
        transform.position.y = -360.0f + radius;
    }

    if (transform.position.y >= 360.0f - radius) {
        transform.position.y = 360.0f - radius;
    }
}