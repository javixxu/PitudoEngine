#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

class ECSManager{

public:
	static ECSManager& getInstance() {
		static ECSManager instance;
		return instance;
	}

	ECSManager(const ECSManager&) = delete;
	ECSManager& operator=(const ECSManager&) = delete;


    void Init();
	void Close();
    Entity CreateEntity();
    void DestroyEntity(Entity entity);

    // Component methods
	template<typename T>
	void RegisterComponent(){
		mComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T&& component){
		mComponentManager->AddComponent<T>(entity, std::forward<T>(component));

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity){
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity){
		return mComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType(){
		return mComponentManager->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem(){
		return mSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature){
		mSystemManager->SetSignature<T>(signature);
	}

	void UpdateSystems(float deltaTime) {
		mSystemManager->UpdateSystems(deltaTime);
	}

private:
	ECSManager() = default;

	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<SystemManager> mSystemManager;
};