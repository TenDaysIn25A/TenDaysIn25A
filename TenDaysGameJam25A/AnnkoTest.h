#pragma once
#include "Renderer.h" // �`����������C�u�����i�K��SetCamera���Ăяo�����Ɓj
#include "Transform2D.h" // �X�P�[�� ��] ���s�ړ����������C�u����
#include "Input.h" // input���g����悤�ɂ��郉�C�u����
#include "DrawEffects.h" // �G�t�F�N�g��`��ł���悤�ɂ��郉�C�u����

class AnnkoTest{
public:

    // ----------------------------------------------
    // �����o�֐�
    // ----------------------------------------------

    AnnkoTest(); // �錾���Ɏ����ŏ�����
    ~AnnkoTest() = default;

    // ����
    // ----------------------------------------------

    /// <summary>
    /// ��������������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V������������
    /// </summary>
    void Update();

    /// <summary>
    /// �`�揈���������Ɂ@��const�ɂ���Ă��̒��ł̒l�̕ύX�͋֎~����Ă���B
    /// </summary>
    void Draw() const;

    // �A�N�Z�b�T (Set�`�Ƃ��AGet�`�Ƃ�)
    // ----------------------------------------------

    /// <summary>
    /// main��GameScene����J�������擾���Ă��������B
    /// </summary>
    /// <param name="camera"></param>
    void SetCamera(const Transform2D& camera);

    // �@�\
    // ----------------------------------------------

    /// <summary>
    /// �ړ�
    /// </summary>
    void Move();

    /// <summary>
    /// ��ʓ��ɃN�����v����B
    /// </summary>
    void ClampInWindow();

    // ----------------------------------------------
    // �����o�ϐ�
    // ----------------------------------------------

    // �V�X�e��
    // ----------------------------------------------
    Renderer renderer;    // �`�惉�C�u����������Ŏg����悤�ɂ��Ă��������B
    Input input;        // ���̓��C�u����������Ŏg����悤�ɂ��Ă��������B
    DrawEffects effect;    // �G�t�F�N�g�`�惉�C�u����������Ŏg����悤�ɂ��Ă��������B

    // �v���C���[�v���p�e�B
    // ----------------------------------------------

    Transform2D transform; // position�Ƃ��錾���Ȃ��Ă�������

    float speed;
    Vector2 direction;
    Vector2 velocity;

    float radius;

    bool isAlive;
};