#pragma once
#include "Coreminimal.h"

class GameEngine;
class RigidBodyComponent;

struct RigidBody
{
    RigidBodyComponent* rigidBodyComponent;
    PxRigidActor* actor;
    BOOL staticObject;//静的オブジェクトかどうか

};

class PhysixEngine
{
public:
    PhysixEngine(GameEngine* gameEngine);
    ~PhysixEngine();

    void Update(void);

    void AddRigidBodyStatic(RigidBodyComponent* rb);
    void AddRigidBodyDynamic(RigidBodyComponent* rb);

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
    // PVDと通信する際に必要
    PxPvd* pvd;

    list<RigidBody*> rigidBodyList;

};
