//======================================================================================
//
//�p�[�e�B�N���̏���[Player.h]
//Author;���}���@�V
//
//======================================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�p�[�e�B�N���̎��
typedef enum
{
	PARTICLE_TYPE_NONE = 0,								//�}�Y���t���b�V��
	PARTICLE_TYPE_EXPLO,							//����
	PARTICLE_TYPE_MAX
}PARTICLE_TYPE;

//�p�[�e�B�N���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 move;				//�ړ���
	D3DXVECTOR3 rot;				//����
	D3DXCOLOR col;					//�F
	PARTICLE_TYPE type;			//���
	float fRadius;					//���a(�傫��)
	int nLife;						//����
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Particle;

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PARTICLE_TYPE type);

#endif