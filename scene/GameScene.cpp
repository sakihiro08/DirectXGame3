#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"AxisIndicator.h"
#include"PrimitiveDrawer.h"
#include"SetMatrix.h"
using namespace MathUtility;
GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugcamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//画像読み込み
	texturehandle_ = TextureManager::Load("hadesu.jpg");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	debugcamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugcamera_->GetViewProjection());
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugcamera_->GetViewProjection());
	/*スケーリング*/
		worldTransform_.scale_ = { 5,5,5 };
		worldTransform_.rotation_ = { 0.0f,Dtor(45.0f),Dtor(45.0f) };
worldTransform_.translation_ = { 10,10,10 };	



 //  Matrix4 matScale; 
	//matScale = MathUtility::Matrix4Identity();
	//matScale.m[0][0] = worldTransform_.scale_.x;
	//	matScale.m[1][1]= worldTransform_.scale_.y;
	//	matScale.m[2][2]= worldTransform_.scale_.z;
	//

	////回転
	//
	//
	//Matrix4 matRotZ;
	//matRotZ = MathUtility::Matrix4Identity();
	//matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	// matRotZ.m[0][1]= sin(worldTransform_.scale_.z);
	// matRotZ.m[1][0]=-sin(worldTransform_.scale_.z);
	// matRotZ.m[1][1] =cos( worldTransform_.scale_.z);
	//

	////x軸
	//
	//Matrix4 matRotX;
	//matRotX = MathUtility::Matrix4Identity();
	//matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	//matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	//matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	//matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	//

	////Y軸
	//
	//Matrix4 matRotY;
	//matRotY = MathUtility::Matrix4Identity();
	//matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	//matRotY.m[0][2] = sin(worldTransform_.rotation_.y);
	//matRotY.m[2][0] = -sin(worldTransform_.rotation_.y);
	//matRotY.m[2][2] = cos(worldTransform_.rotation_.y);
	//
	//
	////回転合成
	//
	//Matrix4 matRot;
	//
	//matRotZ = MathUtility::Matrix4Identity();
	//matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	//matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	//matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	//matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	//matRotX = MathUtility::Matrix4Identity();
	//matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	//matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	//matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	//matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	//matRotY = MathUtility::Matrix4Identity();
	//matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	//matRotY.m[0][2] = sin(worldTransform_.rotation_.y);
	//matRotY.m[2][0] = -sin(worldTransform_.rotation_.y);
	//matRotY.m[2][2] = cos(worldTransform_.rotation_.y);
	//matRot = matRotZ * matRotX * matRotY;
	//
	////平行
	//
	//Matrix4 matTrans = MathUtility::Matrix4Identity();
	//matTrans.m[3][0]= worldTransform_.translation_.x;
	//matTrans.m[3][1]= worldTransform_.translation_.y;
	//matTrans.m[3][2]= worldTransform_.translation_.z;
	//
	//
	//
	//worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	//worldTransform_.matWorld_ *= matScale ;
	//worldTransform_.matWorld_ *= matRot;
	//worldTransform_.matWorld_ *= matTrans;
	//worldTransform_.TransferMatrix();

}

void GameScene::Update()
{
	debugcamera_->Update();
	worldTransform_.translation_.x += 0.1f;
	SetMatrix(worldTransform_);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//model_->Draw(worldTransform_, viewProjection_, texturehandle_);
	model_->Draw(worldTransform_, debugcamera_->GetViewProjection(), texturehandle_);
	PrimitiveDrawer::GetInstance()->DrawLine3d({ 0, 1, 0 }, { 2, 1, 0 }, { 1, 1, 1, 1 });
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
