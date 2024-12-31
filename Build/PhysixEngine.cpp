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
    // Foundationのインスタンス化
    if (foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback); !foundation) {
        return;
    }
    // PVDと接続する設定
    if (pvd = physx::PxCreatePvd(*foundation); pvd) {
        // PVD側のデフォルトポートは5425
        PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        b= pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

    }
    // Physicsのインスタンス化
    if (physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true); !physics) {
        return;
    }
    // 拡張機能用
    if (!PxInitExtensions(*physics,pvd)) {
        return;
    }

    // 処理に使うスレッドを指定する
    dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    // 空間の設定
    PxSceneDesc scene_desc(physics->getTolerancesScale());
    scene_desc.gravity = physx::PxVec3(0, -9.81, 0);
    scene_desc.filterShader = physx::PxDefaultSimulationFilterShader;
    scene_desc.cpuDispatcher = dispatcher;


    // 空間のインスタンス化
    scene = physics->createScene(scene_desc);
    // PVDの表示設定
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

// シミュレーション更新関数
void PhysixEngine::Update(void)
{
    bool b;
    b = scene->simulate(1.0f / 60.0f);
    b = scene->fetchResults(true);
}

void PhysixEngine::AddRigidBodyStatic(RigidBodyComponent* rb)
{
    // 絶対に動くことのない(静的)剛体を作成
    PxRigidStatic* rigid_static= physics->createRigidStatic(PxTransform(PxIdentity));
    // 形状(Box)を作成
    PxShape* box_shape
        = physics->createShape(
            // Boxの大きさ
            physx::PxBoxGeometry(1.f, 1.f, 1.f),
            // 摩擦係数と反発係数の設定
            *physics->createMaterial(0.5f, 0.5f, 0.5f)
        );
    // 形状のローカル座標を設定
    box_shape->setLocalPose(physx::PxTransform(PxIdentity));
    // 形状を紐づけ
    rigid_static->attachShape(*box_shape);
    // 剛体を空間に追加
    scene->addActor(*rigid_static);
}

void PhysixEngine::AddRigidBodyDynamic(RigidBodyComponent* rb)
{
}
