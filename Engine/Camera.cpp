#include "camera.h"
#include "Direct3D.h"
#include "Input.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMMATRIX _billBoard;

//カメラの回転
float yaw = 0.0f; // Y軸回転
float pitch = -0.3f; // X軸回転

//カメラ距離
float distance = 15.0f;

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 3, -10);	//カメラの位置
	_target = XMFLOAT3( 0, 0, 0);	//カメラの焦点

	constexpr float fov = XMConvertToRadians(90.0f);	//視野角

	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(fov, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	if (isMove)
	{
		//マウス移動量
		XMFLOAT3 mouseMove = Input::GetMouseMove();

		float sensitivity = 0.005f; // マウス感度

		yaw += mouseMove.x * sensitivity; // Yawを更新
		pitch += mouseMove.y * sensitivity; // Pitchを更新

		// ピッチの制限
		constexpr float maxPitch = XMConvertToRadians(89.0f); // ピッチの最大
		constexpr float minPitch = XMConvertToRadians(5.0f); // ピッチの最小
		if (pitch > maxPitch) {
			pitch = maxPitch;
		}
		if (pitch < minPitch) {
			pitch = minPitch;
		}
	}

	// カメラの位置を更新
	_position.x = _target.x - cosf(pitch) * sinf(yaw) * distance;
	_position.y = _target.y + sinf(pitch) * distance;
	_position.z = _target.z - cosf(pitch) * cosf(yaw) * distance;

	//ビュー行列
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));


	//ビルボード行列
	//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target)- XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//焦点を設定
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

//位置を設定
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//焦点を取得
XMFLOAT3 Camera::GetTarget() { return _target; }

//位置を取得
XMFLOAT3 Camera::GetPosition() { return _position; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix(){	return _billBoard; }

float Camera::GetYaw(){ return yaw; }

bool Camera::isMove = false; // カメラの操作を有効にするかどうか
void Camera::SetEnableControl(bool enable){ isMove = enable; }
