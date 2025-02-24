#include "ECSManager.h"
#include <random>

struct Vec3{
    float x;
    float y;
    float z;
    Vec3(float _x,float _y, float _z):
        x(_x),y(_y),z(_z){
    };
};

struct Gravity
{
	Vec3 force;
};

struct RigidBody
{
	Vec3 velocity;
	Vec3 acceleration;
};

struct Transform
{
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
};


class PhysicsSystem: public System{
public:
    void Update(float deltaTime) override{
    };
};


ECSManager ecsManager;

int main()
{
	ecsManager.Init();

	ecsManager.RegisterComponent<Gravity>();
	ecsManager.RegisterComponent<RigidBody>();
	ecsManager.RegisterComponent<Transform>();

	auto physicsSystem = ecsManager.RegisterSystem<PhysicsSystem>();

	Signature signature;
	signature.set(ecsManager.GetComponentType<Gravity>());
	signature.set(ecsManager.GetComponentType<RigidBody>());
	signature.set(ecsManager.GetComponentType<Transform>());
	ecsManager.SetSystemSignature<PhysicsSystem>(signature);

	std::vector<Entity> entities(MAX_ENTITIES);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);

	for (auto& entity : entities)
	{
		entity = ecsManager.CreateEntity();

		ecsManager.AddComponent(
			entity,
			Gravity{Vec3(0.0f, randGravity(generator), 0.0f)});

        ecsManager.AddComponent(
			entity,
			RigidBody{
				.velocity = Vec3(0.0f, 0.0f, 0.0f),
				.acceleration = Vec3(0.0f, 0.0f, 0.0f)
			});

        ecsManager.AddComponent(
			entity,
			Transform{
				.position = Vec3(randPosition(generator), randPosition(generator), randPosition(generator)),
				.rotation = Vec3(randRotation(generator), randRotation(generator), randRotation(generator)),
				.scale = Vec3(scale, scale, scale)
			});
	}
}