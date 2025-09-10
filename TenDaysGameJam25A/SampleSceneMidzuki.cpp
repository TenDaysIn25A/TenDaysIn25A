#include "SampleSceneMidzuki.h"
#include"Dlib.h"

SampleSceneMidzuki::SampleSceneMidzuki() { Initialize(); }

void SampleSceneMidzuki::Initialize() {
	// ここで各初期化を行う。

	samplePlayer.Initialize();

	player.Initialize();
	player.height = 79.0f;
	player.grHandleCaracterDimTwo = Novice::LoadTexture("./Resources/images/Chiriri.png");

	
	stage2Scene.Initialize();
	light.Initialize();

	currentDimension = DimensionState::TWO;

	box.position = { -150,0.0f };
	boxWidth = 80.0f;
	boxHeight = 160.0f;
	
	playerLeftTop.position = { player.transform.position.x - player.width / 2.0f,player.transform.position.y + player.height / 2.0f };
	playerRightTop.position = { player.transform.position.x + player.width / 2.0f,player.transform.position.y + player.height / 2.0f };
	playerLeftBottom.position = { player.transform.position.x - player.width / 2.0f,player.transform.position.y - player.height / 2.0f };
	playerRightBottom.position = { player.transform.position.x + player.width / 2.0f,player.transform.position.y - player.height / 2.0f };

	playerTheta = 0.0f;
	playerRotateTheta = 180.0f * float(M_PI) / 60.0f;

	radius = { 5.0f,5.0f };

	leftTopColor = 0xFFFFFFFF;
	rightTopColor = 0xFFFFFFFF;
	leftBottomColor = 0xFFFFFFFF;
	rightBottomColor = 0xFFFFFFFF;

	//下あご
	chochinMouthBottom.position = { kChochinMouthOffsetX,kChochinMouthOffsetY };
	chochinMouthBottomWidth = 480.0f;
	chochinMouthBottomHeight = 480.0f;
	chochinMouthBottomTheta = 0.0f;
	grHandleChochinMouthBottom0 = Novice::LoadTexture("./Resources/images/chochinMouthBottom0.png");
	grHandleChochinMouthBottom1 = Novice::LoadTexture("./Resources/images/chochinMouthBottom1.png");
	grHandleChochinMouthBottom2 = Novice::LoadTexture("./Resources/images/chochinMouthBottom2.png");
	grHandleChochinMouthBottom3 = Novice::LoadTexture("./Resources/images/chochinMouthBottom3.png");


	//上あご
	chochinMouthTop.position = { kChochinMouthOffsetX,kChochinMouthOffsetY };
	chochinMouthTopWidth = 480.0f;
	chochinMouthTopHeight = 480.0f;
	chochinMouthTopTheta = 0.0f;
	grHandleChochinMouthTop0 = Novice::LoadTexture("./Resources/images/chochinMouthTop0.png");
	grHandleChochinMouthTop1 = Novice::LoadTexture("./Resources/images/chochinMouthTop1.png");
	grHandleChochinMouthTop2 = Novice::LoadTexture("./Resources/images/chochinMouthTop2.png");
	grHandleChochinMouthTop3 = Novice::LoadTexture("./Resources/images/chochinMouthTop3.png");
	chochinAnimationCount = 0;


	//あごの動き
	chochinAmplitudeX = 30.0f;
	chochinAmplitudeY = 36.0f;
	chochinWavingThetaX = float(M_PI) / 2.0f;
	chochinWavingThetaY = 0.0f;

	//目
	chochinEies.position = { kChochinEiesOffsetX,kChochinEiesOffsetY };
	chochinEiesWidth = 96.0f;
	chochinEiesHeight = 96.0f;
	grHandleChochinEies = Novice::LoadTexture("./Resources/images/chochinEies.png");
	chochinEiesTheta = float(M_PI) * 0.0f;
	chochinEiesRotateTimer = 4;

	//提灯
	chochinLight.position = { 0.0f,0.0f };
	chochinLightWidth = 480.0f;
	chochinLightHeight = 220.0f;
	grHandleChochinLight0 = Novice::LoadTexture("./Resources/images/chochinLight0.png");
	grHandleChochinLight1 = Novice::LoadTexture("./Resources/images/chochinLight1.png");
	grHandleChochinLight2 = Novice::LoadTexture("./Resources/images/chochinLight2.png");
	grHandleChochinLight3 = Novice::LoadTexture("./Resources/images/chochinLight3.png");
	chochinLightTheta = 0.0f;
	chochinLightThetaSpeed = 0.5f;
	chochinLightIsActive = false;

	chochinThetaSpeed = 0.07f;
	chochinColor = 0x00EEEEFF;

	//ステージ選択＿テキスト
	chochinStageWhiteText.position = { kChochinStageWhiteTextOffset };
	grHandleChochinStageWhiteText = Novice::LoadTexture("./Resources/images/chochinStageWhiteTxt.png");
	chochinStageWhiteTextWidth = 418.0f;
	chochinStageWhiteTextHeight = 60.0f;

	chochinStageColorText.position = { chochinStageWhiteText.position.x + chochinStageColorTextOffsetX,chochinStageWhiteText.position.y };
	grHandleChochinStageColorText = Novice::LoadTexture("./Resources/images/chochinStageColorTxt.png");
	chochinStageColorTextWidth = 128.0f;
	chochinStageColorTextHeight = 60.0f;
	chochinStageTextColorChongeTimer = 180;

	textAmplitudeY = 30.0f;
	textWavingThetaY = 0.0f;
	chochinStageColorTextColor = 0xFFFFFFFF;
}

void SampleSceneMidzuki::Update() {
	// ここで各更新処理を行う
	SetCamera();

	input.Update();

	player.Update();

	stage2Scene.stage2Boss.playerPos = player.transform.position;

	stage2Scene.Update();

	playerLeftTop.position = { player.transform.position.x - player.width / 2.0f,player.transform.position.y + player.height / 2.0f };
	playerRightTop.position = { player.transform.position.x + player.width / 2.0f,player.transform.position.y + player.height / 2.0f };
	playerLeftBottom.position = { player.transform.position.x - player.width / 2.0f,player.transform.position.y - player.height / 2.0f };
	playerRightBottom.position = { player.transform.position.x + player.width / 2.0f,player.transform.position.y - player.height / 2.0f };


	if (light.isPlayerInTheShadow(box, boxWidth, boxHeight, playerLeftTop.position)) {
		leftTopColor = 0xFF0000FF;
	} else {
		leftTopColor = 0xFFFFFFFF;
	}

	if (light.isPlayerInTheShadow(box, boxWidth, boxHeight, playerRightTop.position)) {
		rightTopColor = 0xFF0000FF;
	} else {
		rightTopColor = 0xFFFFFFFF;
	}

	if (light.isPlayerInTheShadow(box, boxWidth, boxHeight, playerLeftBottom.position)) {
		leftBottomColor = 0xFF0000FF;
	} else {
		leftBottomColor = 0xFFFFFFFF;
	}

	if (light.isPlayerInTheShadow(box, boxWidth, boxHeight, playerRightBottom.position)) {
		rightBottomColor = 0xFF0000FF;
	} else {
		rightBottomColor = 0xFFFFFFFF;
	}


	if (input.GetKey(DIK_UP)) {
		light.transform.position.y++;
	}

	if (input.GetKey(DIK_LEFT)) {
		light.transform.position.x--;
	}

	if (input.GetKey(DIK_DOWN)) {
		light.transform.position.y--;
	}

	if (input.GetKey(DIK_RIGHT)) {
		light.transform.position.x++;
	}

	if (input.GetKeyTrigger(DIK_SPACE)) {
		if (chochinColor == 0x00EEEEFF) {
			chochinColor = 0xEEEE00FF;


		} else {
			chochinColor = 0x00EEEEFF;
		}

		chochinLightIsActive = !chochinLightIsActive;

		if (chochinLightIsActive) {

			chochinLightThetaSpeed *= 2.0f;
		} else {

			chochinLightThetaSpeed /= 2.0f;

		}

	}

	chochinMouthBottom.position.x = cosf(chochinWavingThetaX) * chochinAmplitudeX + kChochinMouthOffsetX;
	chochinMouthBottom.position.y = sinf(chochinWavingThetaY) * chochinAmplitudeY + kChochinMouthOffsetY;



	if (chochinAnimationCount > 3) {
		chochinAnimationCount = 0;
	} else {
		chochinAnimationCount++;
	}

	chochinMouthTop.position.x = cosf(chochinWavingThetaX) * chochinAmplitudeX + kChochinMouthOffsetX;
	chochinMouthTop.position.y = sinf(chochinWavingThetaY) * chochinAmplitudeY + kChochinMouthOffsetY;

	chochinEies.position.x = chochinMouthBottom.position.x + kChochinEiesOffsetX;
	chochinEies.position.y = chochinMouthBottom.position.y + kChochinEiesOffsetY;

	chochinLight.position.x = chochinMouthBottom.position.x + kChochinLightOffsetX;
	chochinLight.position.y = chochinMouthBottom.position.y + kChochinLightOffsetY;

	if (chochinLightIsActive) {

		if (chochinLightTheta > 30.0f) {
			chochinLightThetaSpeed = -1.0f;
			chochinLightTheta = 30.0f;
		} else if (chochinLightTheta < 0.0f) {
			chochinLightThetaSpeed = 1.0f;
			chochinLightTheta = 0.0f;
		}

	} else {

		if (chochinLightTheta >  30.0f) {
			chochinLightThetaSpeed = -0.5f;
		} else if (chochinLightTheta < 0.0f) {
			chochinLightThetaSpeed = 0.5f;
		}

	}

	//Novice::ScreenPrintf(116, 116, "%f", chochinLightThetaSpeed);

	chochinLightTheta += chochinLightThetaSpeed;

	if (chochinEiesRotateTimer > 0) {
		chochinEiesRotateTimer--;
	} else {
		chochinEiesTheta += float(M_PI) / 2.0f;

		if (chochinColor == 0x00EEEEFF) {
			chochinEiesRotateTimer = 4;


		} else {
			chochinEiesRotateTimer = 1;
		}
	}

	if (chochinColor == 0x00EEEEFF) {

		chochinWavingThetaX += float(M_PI) / 90.0f;
		chochinWavingThetaY += float(M_PI) / 60.0f;
	} else {
		chochinWavingThetaX += float(M_PI) / 60.0f;
		chochinWavingThetaY += float(M_PI) / 30.0f;
	}

	chochinMouthBottomTheta += chochinThetaSpeed;
	chochinMouthTopTheta -= chochinThetaSpeed;

	if (chochinMouthBottomTheta > 3.0f || chochinMouthBottomTheta < 0.0f) {
		chochinThetaSpeed *= -1.0f;
	}

	chochinStageWhiteText.position.y = sinf(textWavingThetaY) * textAmplitudeY + kChochinStageWhiteTextOffset.y;

	textWavingThetaY += float(M_PI) / 60.0f;

	chochinStageColorText.position.y = chochinStageWhiteText.position.y;

	if (chochinStageTextColorChongeTimer > 0) {
		chochinStageTextColorChongeTimer--;

		if (chochinStageTextColorChongeTimer == 60) {
			chochinStageColorTextColor = 0x00FFFFFF;

		} else if (chochinStageTextColorChongeTimer == 55) {
			chochinStageColorTextColor = 0x00FFFFFF;
		} else if (chochinStageTextColorChongeTimer == 51) {
			chochinStageColorTextColor = 0x00FFFFFF;

		} else if (chochinStageTextColorChongeTimer == 120) {
			chochinStageColorTextColor = 0x00FFFFFF;
		}

		if (chochinStageTextColorChongeTimer == 57) {
			chochinStageColorTextColor = 0xFFFFFFFF;

		} else if (chochinStageTextColorChongeTimer == 53) {
			chochinStageColorTextColor = 0xFFFFFFFF;
		} else if (chochinStageTextColorChongeTimer == 41) {
			chochinStageColorTextColor = 0xFFFFFFFF;
		} else if (chochinStageTextColorChongeTimer == 116) {
			chochinStageColorTextColor = 0xFFFFFFFF;
		}

		if (chochinStageTextColorChongeTimer == 160) {
			chochinStageColorTextColor = 0xFFFFFFFF;
		}

	} else {
		chochinStageTextColorChongeTimer = 180;
		chochinStageColorTextColor = 0xFFFF00FF;
	}

	player.transform.Rotate(10.0f);


	CheckHitAll();
}

void SampleSceneMidzuki::CheckHitAll() {

	
}

void SampleSceneMidzuki::Draw() const {
	// ここで各描画を行う。

	// 一次元の背景_黒
	Novice::DrawBox(
		0, 0,
		1280, 720,
		0.0f,
		0x000000FF,
		kFillModeSolid
	);

	// ノーツの描画

	

	// プレイヤーの描画
	//player.Draw();

	renderer.DrawSprite(player.transform, player.width, player.height, 0.0f, player.grHandleCaracterDimTwo, 0xFFFFFFFF);

	//Novice::ScreenPrintf(0, 0, "parryable%d", player.parry.isParryAble);

	if (player.parry.parryState == ParryState::NONE) {
		//Novice::ScreenPrintf(0, 16, "NONE");
	} else if (player.parry.parryState == ParryState::NORMAL) {
		//Novice::ScreenPrintf(0, 16, "NOMAL");
	} else if (player.parry.parryState == ParryState::JUST) {
		//Novice::ScreenPrintf(0, 16, "JUST");
	} else {
		//Novice::ScreenPrintf(0, 16, "else");
	}


	//Novice::ScreenPrintf(0, 32, "%d", player.isUpDamage);

	//Novice::ScreenPrintf(0, 48, "%d", player.damageUpTime);

	//Novice::ScreenPrintf(0, 64, "%d", player.bullets[0].damage);



	//renderer.DrawEllipse(playerLeftTop, radius, { 0,0 }, 0.0f, leftTopColor, kFillModeSolid);
	//renderer.DrawEllipse(playerRightTop, radius, { 0,0 }, 0.0f, rightTopColor, kFillModeSolid);
	//renderer.DrawEllipse(playerLeftBottom, radius, { 0,0 }, 0.0f, leftBottomColor, kFillModeSolid);
	//renderer.DrawEllipse(playerRightBottom, radius, { 0,0 }, 0.0f, rightBottomColor, kFillModeSolid);
	//renderer.DrawEllipse(light.transform, light.radius, { 0,0 }, 0.0f, 0xFFFF00FF, kFillModeSolid);

	//renderer.DrawBox(box, boxWidth, boxHeight, 0.0f, 0xFFFFFFFF, kFillModeSolid);

	//if (chochinAnimationCount == 0) {
	//	renderer.DrawSprite(chochinMouthBottom, chochinMouthBottomWidth, chochinMouthBottomHeight, chochinMouthBottomTheta, grHandleChochinMouthBottom0, chochinColor);
	//	renderer.DrawSprite(chochinMouthTop, chochinMouthTopWidth, chochinMouthTopHeight, chochinMouthTopTheta, grHandleChochinMouthTop0, chochinColor);
	//	renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleChochinLight0, chochinColor);
	//} else if (chochinAnimationCount == 1) {

	//	renderer.DrawSprite(chochinMouthBottom, chochinMouthBottomWidth, chochinMouthBottomHeight, chochinMouthBottomTheta, grHandleChochinMouthBottom1, chochinColor);
	//	renderer.DrawSprite(chochinMouthTop, chochinMouthTopWidth, chochinMouthTopHeight, chochinMouthTopTheta, grHandleChochinMouthTop1, chochinColor);
	//	renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleChochinLight1, chochinColor);

	//} else if (chochinAnimationCount == 2) {

	//	renderer.DrawSprite(chochinMouthBottom, chochinMouthBottomWidth, chochinMouthBottomHeight, chochinMouthBottomTheta, grHandleChochinMouthBottom2, chochinColor);
	//	renderer.DrawSprite(chochinMouthTop, chochinMouthTopWidth, chochinMouthTopHeight, chochinMouthTopTheta, grHandleChochinMouthTop2, chochinColor);
	//	renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleChochinLight2, chochinColor);

	//} else {

	//	renderer.DrawSprite(chochinMouthBottom, chochinMouthBottomWidth, chochinMouthBottomHeight, chochinMouthBottomTheta, grHandleChochinMouthBottom3, chochinColor);
	//	renderer.DrawSprite(chochinMouthTop, chochinMouthTopWidth, chochinMouthTopHeight, chochinMouthTopTheta, grHandleChochinMouthTop3, chochinColor);
	//	renderer.DrawSprite(chochinLight, chochinLightWidth, chochinLightHeight, chochinLightTheta, grHandleChochinLight3, chochinColor);

	//}

	//renderer.DrawSprite(chochinEies, chochinEiesWidth, chochinEiesHeight, chochinEiesTheta * 180 / float(M_PI), grHandleChochinEies, chochinColor);
	//

	//renderer.DrawSprite(chochinStageWhiteText, chochinStageWhiteTextWidth, chochinStageWhiteTextHeight, 0.0f, grHandleChochinStageWhiteText, 0xFFFFFFFF);
	//renderer.DrawSprite(chochinStageColorText, chochinStageColorTextWidth, chochinStageColorTextHeight, 0.0f, grHandleChochinStageColorText, chochinStageColorTextColor);

	stage2Scene.Draw();
}

void SampleSceneMidzuki::SetCamera() {
	// ここで各SetCameraを行う。

	samplePlayer.SetCamera(camera);
}
