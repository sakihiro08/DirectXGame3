#include "SetMatrix.h"
#include <MathUtility.h>
#include <Math.h>
using namespace MathUtility;


// �s��̐ݒ�
void SetMatrix(WorldTransform& WT)
{
	// �X�P�[�����O�s���錾
	Matrix4 matScale = Matrix4Identity();
	// �X�P�[�����O�{�����s��ɐݒ肷��
	matScale.m[0][0] = WT.scale_.x;
	matScale.m[1][1] = WT.scale_.y;
	matScale.m[2][2] = WT.scale_.z;


	// Z����]�s���錾
	Matrix4 matRotZ;
	matRotZ = Matrix4Identity();;
	// Z����]�s��̊e�v�f��ݒ肷��
	matRotZ.m[0][0] = cosf(WT.rotation_.z);
	matRotZ.m[0][1] = sinf(WT.rotation_.z);
	matRotZ.m[1][0] = -sinf(WT.rotation_.z);
	matRotZ.m[1][1] = cosf(WT.rotation_.z);

	// X����]�s���錾
	Matrix4 matRotX;
	matRotX = Matrix4Identity();;
	// X����]�s��̊e�v�f��ݒ肷��
	matRotX.m[1][1] = cosf(WT.rotation_.x);
	matRotX.m[1][2] = sinf(WT.rotation_.x);
	matRotX.m[2][1] = -sinf(WT.rotation_.x);
	matRotX.m[2][2] = cosf(WT.rotation_.x);

	// Y����]�s���錾
	Matrix4 matRotY;
	matRotY = Matrix4Identity();
	// Y����]�s��̊e�v�f��ݒ肷��
	matRotY.m[0][0] = cosf(WT.rotation_.y);
	matRotY.m[2][0] = sinf(WT.rotation_.y);
	matRotY.m[0][2] = -sinf(WT.rotation_.y);
	matRotY.m[2][2] = cosf(WT.rotation_.y);

	Matrix4 matRot;
	matRot = matRotZ * matRotX * matRotY;

	// ���s�ړ��s���錾
	Matrix4 matTrans = Matrix4Identity();

	// �ړ��ʂ��s��ɐݒ肷��
	matTrans.m[3][0] = WT.translation_.x;
	matTrans.m[3][1] = WT.translation_.y;
	matTrans.m[3][2] = WT.translation_.z;

	// �s��̍���
	WT.matWorld_ = matScale * matRot * matTrans;

	// �s��̓]��
	WT.TransferMatrix();
}
