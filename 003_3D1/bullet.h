//======================================================================================
//
//�e�̏���[Player.h]
//Author;���}���@�V
//
//======================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

#define SCREEN_RIGHT		(640)			//��ʉE���̓����蔻��

//======�G�ݒ�======//
#define BULLET_SIZEX		(20.0f)			//�G�̃T�C�YX
#define BULLET_SIZEY		(20.0f)			//�G�̃T�C�YY

//�e�̎��(��ނ𑝂₵�����Ȃ炱����)
typedef enum
{
	BULLETTYPE_PLAYER = 0,			//�v���C���[�̒e
	BULLETTYPE_STAGE1,				//�X�e�[�W1�̓G���g��
	BULLETTYPE_MAX
}BULLETTYPE;

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 move;				//�ړ���
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX mtxWorldBullet;	//���[���h�}�g���b�N�X
	BULLETTYPE type;				//���
	int nLife;						//����
	int nIdxShadow;					//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
	bool bUse;						//�g�p���Ă��邩�ǂ���
} Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type);
int BulletCnt(void);
void DrawDebug(void);
Bullet *GetBullet(void);

#endif
