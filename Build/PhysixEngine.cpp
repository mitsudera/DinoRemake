#include "PhysixEngine.h"
#include "GameEngine.h"
#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

PhysxEngine::PhysxEngine(GameEngine* gameEngine)
{
    pGameEngine = gameEngine;
    physics = nullptr;
    foundation = nullptr;
    dispatcher = nullptr;
    scene = nullptr;
    material = nullptr;
    cudaCtxMgr = nullptr;
    pvd = nullptr;
    simulationEventCallback = new PhysxSimulationEventCallback();

    // Foundation�̃C���X�^���X��
    foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback);
    // PVD�Ɛڑ�����ݒ�
    pvd = PxCreatePvd(*foundation);

    PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

    // Physics�̃C���X�^���X��
    physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true);
    // �g���@�\�p
    PxInitExtensions(*physics, pvd);

    // �����Ɏg���X���b�h���w�肷��
    dispatcher = PxDefaultCpuDispatcherCreate(2);
    // ��Ԃ̐ݒ�
    PxSceneDesc scene_desc(physics->getTolerancesScale());
    scene_desc.gravity = PxVec3(0, -9.81, 0);
    scene_desc.filterShader = PxDefaultSimulationFilterShader;
    scene_desc.cpuDispatcher = dispatcher;

    // �V�~�����[�V�����C�x���g�R�[���o�b�N�̐ݒ�
    scene_desc.simulationEventCallback = simulationEventCallback;

    // ��Ԃ̃C���X�^���X��
    scene = physics->createScene(scene_desc);
    // PVD�̕\���ݒ�
    if (PxPvdSceneClient* pvd_client = scene->getScenePvdClient(); pvd_client) {
        pvd_client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvd_client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvd_client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }

    material = physics->createMaterial(0.0f, 0.0f, 0.0f);
}

PhysxEngine::~PhysxEngine()
{
    PxCloseExtensions();
    scene->release();
    dispatcher->release();
    physics->release();
    delete simulationEventCallback;
    if (pvd) {
        pvd->disconnect();
        PxPvdTransport* transport = pvd->getTransport();
        pvd->release();
        transport->release();
    }
    foundation->release();
}

void PhysxEngine::Update(void)
{

    for (PhysxActor* actor : actorList)
    {
        actor->actor->setGlobalPose(PxTransform(XMFLOAT3ToPxVec3(actor->collider->GetWorldPos())));
        PxTransform transform = actor->actor->getGlobalPose();
    }

    // �V�~�����[�V�����̍X�V
    scene->simulate(pGameEngine->GetFixedDeltaTime());
    scene->fetchResults(true);

    // �e�I�u�W�F�N�g�̐ڐG����
    for (PhysxActor* actor : actorList)
    {
        PxTransform transform = actor->actor->getGlobalPose();

        actor->collider->GetTransFormComponent()->SetPosition(PxVec3ToXMFLOAT3(transform.p));

        if (actor->isSimulation)
        {
            // �K�v�ȏ�����ǉ�
        }
    }
}


void PhysxSimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
    for (PxU32 i = 0; i < nbPairs; i++)
    {
        const PxContactPair& cp = pairs[i];

        if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            PxActor* actor0 = pairHeader.actors[0];
            PxActor* actor1 = pairHeader.actors[1];
        }
    }
}

void PhysxSimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
    for (PxU32 i = 0; i < count; i++)
    {
        const PxTriggerPair& pair = pairs[i];

        if (pair.status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            PxActor* triggerActor = pair.triggerActor;
            PxActor* otherActor = pair.otherActor;

            string name = triggerActor->getName();
        }
    }
}

void PhysxSimulationEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
{
    for (PxU32 i = 0; i < count; i++)
    {
        const PxConstraintInfo& constraint = constraints[i];
    }
}

void PhysxSimulationEventCallback::onWake(PxActor** actors, PxU32 count)
{
    for (PxU32 i = 0; i < count; i++)
    {
        PxActor* actor = actors[i];
    }
}

void PhysxSimulationEventCallback::onSleep(PxActor** actors, PxU32 count)
{
    for (PxU32 i = 0; i < count; i++)
    {
        PxActor* actor = actors[i];
    }
}

void PhysxSimulationEventCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
    for (PxU32 i = 0; i < count; i++)
    {
        const PxRigidBody* body = bodyBuffer[i];
        const PxTransform& pose = poseBuffer[i];
    }
}

void PhysxEngine::AddCollider(ColliderComponent* collider)
{
    switch (collider->GetShape())
    {
    case ColliderComponent::Shape::Point:
    {

    }

        break;
    case ColliderComponent::Shape::Line:
    {

    }

        break;
    case ColliderComponent::Shape::Sphere:
    {

    }

        break;
    case ColliderComponent::Shape::Capsule:
    {

    }

        break;
    case ColliderComponent::Shape::Box:
    {
        BoxColliderComponent* box = static_cast<BoxColliderComponent*>(collider);
        PxShape* shape = physics->createShape(PxBoxGeometry(box->GetSize().x, box->GetSize().y, box->GetSize().z), *material);
        shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
        shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
        PhysxActor* actor = new PhysxActor;
        
        if (collider->GetIsStatic())
        {
            PxRigidStatic* staticBox = physics->createRigidStatic(PxTransform(XMFLOAT3ToPxVec3(box->GetWorldPos())));
            staticBox->attachShape(*shape);
            staticBox->setName(box->GetGameObject()->GetName().c_str());
            scene->addActor(*staticBox);

            actor->actor = staticBox;
            actor->staticObject = TRUE;

        }
        else
        {
            PxRigidDynamic* dynamicBox = physics->createRigidDynamic(PxTransform(XMFLOAT3ToPxVec3(box->GetWorldPos())));
            dynamicBox->attachShape(*shape);
            dynamicBox->setName(box->GetGameObject()->GetName().c_str());
            scene->addActor(*dynamicBox);

            actor->actor = dynamicBox;
            actor->staticObject = FALSE;


        }
        actor->name = box->GetGameObject()->GetName();
        actor->collider = box;
        actor->isSimulation = FALSE;
        actor->rigidBodyComponent = nullptr;

        actorList.push_back(actor);

        break;

    }


    case ColliderComponent::Shape::Terrain:
    {

    }

        break;
    }


}

void PhysxEngine::AddRigidBodyStatic(RigidBodyComponent* rb)
{
    // ��΂ɓ������Ƃ̂Ȃ�(�ÓI)���̂��쐬
    PxRigidStatic* rigidStatic = physics->createRigidStatic(PxTransform(PxIdentity));

    PxShape* boxShape
        = physics->createShape(
            // Box�̑傫��
            PxBoxGeometry(1.f, 1.f, 1.f),
            // ���C�W���Ɣ����W���̐ݒ�
            *physics->createMaterial(0.5f, 0.5f, 0.5f)
        );
    // �`��̃��[�J�����W��ݒ�
    boxShape->setLocalPose(PxTransform(PxIdentity));
    // �`���R�Â�
    rigidStatic->attachShape(*boxShape);
    // ���̂���Ԃɒǉ�
    scene->addActor(*rigidStatic);

    PhysxActor* rigidBody = new PhysxActor;
    rigidBody->actor = rigidStatic;
    rigidBody->rigidBodyComponent = rb;
    rigidBody->staticObject = TRUE;
    actorList.push_back(rigidBody);

}

void PhysxEngine::AddRigidBodyDynamic(RigidBodyComponent* rb)
{
    // ���������Ƃ̂ł���(���I)���̂��쐬
    PxRigidDynamic* rigidDynamic
        = physics->createRigidDynamic(PxTransform(PxIdentity));
    // �`��(Box)���쐬
    PxShape* boxShape
        = physics->createShape(
            // Box�̑傫��
            PxBoxGeometry(1.f, 1.f, 1.f),
            // ���C�W���Ɣ����W���̐ݒ�
            *physics->createMaterial(0.5f, 0.5f, 0.5f)
        );
    // �`���R�Â�
    boxShape->setLocalPose(PxTransform(PxIdentity));
    rigidDynamic->attachShape(*boxShape);

    // ���̂���Ԃɒǉ�
    scene->addActor(*rigidDynamic);

    PhysxActor* rigidBody = new PhysxActor;
    rigidBody->actor = rigidDynamic;
    rigidBody->rigidBodyComponent = rb;
    rigidBody->staticObject = FALSE;
    actorList.push_back(rigidBody);


}

void PhysxEngine::ChangeName(ColliderComponent* com, string newName)
{

    for (PhysxActor* actor : actorList)
    {
        if (actor->collider == com)
        {
            actor->name = newName;
            actor->actor->setName(newName.c_str());
            return;
        }
    }

}
