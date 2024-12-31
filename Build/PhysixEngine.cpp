#include "PhysixEngine.h"
#include "GameEngine.h"
PhysixEngine::PhysixEngine(GameEngine* gameEngine)
{
	pGameEngine = gameEngine;
	this->physics = nullptr;
	this->foundation = nullptr;
	this->dispatcher = nullptr;
	this->scene = nullptr;
	this->material = nullptr;
    this->cudaCtxMgr = nullptr;
    this->pvd = nullptr;
    bool b;
    // Foundation�̃C���X�^���X��
    if (foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback); !foundation) {
        return;
    }
    // PVD�Ɛڑ�����ݒ�
    if (pvd = physx::PxCreatePvd(*foundation); pvd) {
        // PVD���̃f�t�H���g�|�[�g��5425
        PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        b= pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

    }
    // Physics�̃C���X�^���X��
    if (physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true); !physics) {
        return;
    }
    // �g���@�\�p
    if (!PxInitExtensions(*physics,pvd)) {
        return;
    }

    // �����Ɏg���X���b�h���w�肷��
    dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    // ��Ԃ̐ݒ�
    PxSceneDesc scene_desc(physics->getTolerancesScale());
    scene_desc.gravity = physx::PxVec3(0, -9.81, 0);
    scene_desc.filterShader = physx::PxDefaultSimulationFilterShader;
    scene_desc.cpuDispatcher = dispatcher;


    // ��Ԃ̃C���X�^���X��
    scene = physics->createScene(scene_desc);
    // PVD�̕\���ݒ�
    PxPvdSceneClient* pvd_client;
    if (pvd_client = scene->getScenePvdClient(); pvd_client) {
        pvd_client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvd_client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvd_client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }

}

PhysixEngine::~PhysixEngine()
{
    PxCloseExtensions();
    scene->release();
    dispatcher->release();
    physics->release();
    if (pvd) {
        pvd->disconnect();
        PxPvdTransport* transport = pvd->getTransport();
        pvd->release();
        transport->release();
    }
    foundation->release();
}

// �V�~�����[�V�����X�V�֐�
void PhysixEngine::Update(void)
{
    bool b;
    b = scene->simulate(1.0f / 60.0f);
    b = scene->fetchResults(true);
}

void PhysixEngine::AddRigidBodyStatic(RigidBodyComponent* rb)
{
    // ��΂ɓ������Ƃ̂Ȃ�(�ÓI)���̂��쐬
    PxRigidStatic* rigid_static= physics->createRigidStatic(PxTransform(PxIdentity));
    // �`��(Box)���쐬
    PxShape* box_shape
        = physics->createShape(
            // Box�̑傫��
            physx::PxBoxGeometry(1.f, 1.f, 1.f),
            // ���C�W���Ɣ����W���̐ݒ�
            *physics->createMaterial(0.5f, 0.5f, 0.5f)
        );
    // �`��̃��[�J�����W��ݒ�
    box_shape->setLocalPose(physx::PxTransform(PxIdentity));
    // �`���R�Â�
    rigid_static->attachShape(*box_shape);
    // ���̂���Ԃɒǉ�
    scene->addActor(*rigid_static);
}

void PhysixEngine::AddRigidBodyDynamic(RigidBodyComponent* rb)
{
}
