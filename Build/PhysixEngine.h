#pragma once
#include "CoreMinimal.h"


class GameEngine;
class RigidBodyComponent;
class ColliderComponent;

struct PhysxActor
{
    ColliderComponent* collider;
    RigidBodyComponent* rigidBodyComponent;
    PxRigidActor* actor;
    BOOL isSimulation;
    BOOL staticObject; // 静的オブジェクトかどうか
    string name;
};

class PhysxSimulationEventCallback : public PxSimulationEventCallback
{
public:
    
    void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;
    void onTrigger(PxTriggerPair* pairs, PxU32 count) override;
    void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override;
    void onWake(PxActor** actors, PxU32 count) override;
    void onSleep(PxActor** actors, PxU32 count) override;
    void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override;
};

class PhysxEngine
{
public:
    PhysxEngine(GameEngine* gameEngine);
    ~PhysxEngine();

    void Update(void);
    void AddCollider(ColliderComponent* collider);
    void AddRigidBodyStatic(RigidBodyComponent* rb);
    void AddRigidBodyDynamic(RigidBodyComponent* rb);
    void ChangeName(ColliderComponent* com, string newName);

private:
    GameEngine* pGameEngine;
    PxDefaultAllocator defaultAllocator;
    PxDefaultErrorCallback defaultErrorCallback;
    PxPhysics* physics;
    PxFoundation* foundation;
    PxDefaultCpuDispatcher* dispatcher;
    PxScene* scene;
    PxMaterial* material;
    PxCudaContextManager* cudaCtxMgr;
    PxPvd* pvd;
    list<PhysxActor*> actorList;
    PhysxSimulationEventCallback* simulationEventCallback; // シミュレーションイベントコールバック
};

