#include "Engine.h"
#include <iostream>

#include <tigr/tigr.h>
#include <ecs/ECSManager.h>

#include "Vec2.h"

#include "RenderSystem.h"
#include "InputSystem.h"
#include "ColliderSystem.h"

#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"

/*
        Input == DONE /(FALTA CLIKS RATON)
        Update Sistemas 
        Fisicas
        Colliders   
        Render == DONE
*/



namespace PitudoEngine {
    bool Engine::Init(){
        m_bIsRunning = true;
        m_screen = tigrWindow(800, 600, "PitudoEngine", 0);
        std::cout << "Initializing Tiger\n";
       
        ecsManager = &ECSManager::getInstance();
        ecsManager->Init();

        return !!m_screen;// conv a explicito
    }

    void Engine::SetUp(){
        ecsManager->RegisterComponent<Transform>();
        ecsManager->RegisterComponent<Sprite>();
        ecsManager->RegisterComponent<Collider>();

        auto inputSystem = ecsManager->RegisterSystem<InputSystem>();
        inputSystem->setContext(m_screen); //PRIMERO EN REGISTRAR PUES ES EL INPUT

        auto renderSystem = ecsManager->RegisterSystem<RenderSystem>();
        renderSystem->setContext(m_screen); //ULTIMO EN REGISTRAR PUES LA RENDERIZACION ES LO ULTIMO DEL BUCLE DE JUEGO


        auto colliderSystem = ecsManager->RegisterSystem<ColliderSystem>();
        

        Signature signature;
        signature.set(ecsManager->GetComponentType<Transform>());
        signature.set(ecsManager->GetComponentType<Sprite>());
        signature.set(ecsManager->GetComponentType<Collider>());
        ecsManager->SetSystemSignature<RenderSystem>(signature);

        auto entity = ecsManager->CreateEntity();

        ecsManager->AddComponent<Transform>(entity, Vec2(-1,300), Vec2(1,1), 0.0f);
        ecsManager->AddComponent<Sprite>(entity, &ecsManager->GetComponent<Transform>(entity), "../data/mrkrabs.png",Vec2(0.5f));
        ecsManager->AddComponent<Collider>(entity, &ecsManager->GetComponent<Transform>(entity),ColliderShape::CIRCLE,Vec2(0.5f));

        Transform* trs = &ecsManager->GetComponent<Transform>(entity);
        trs->scale = { 1.0f, 1.0f };

        Sprite* sprite = &ecsManager->GetComponent<Sprite>(entity);
        Collider* coll = &ecsManager->GetComponent<Collider>(entity);
        coll->m_Size = sprite->getImageSize() / 2.0F;

        entity = ecsManager->CreateEntity();

        ecsManager->AddComponent<Transform>(entity, Vec2(600, 300), Vec2(1, 1), 0.0f);
        ecsManager->AddComponent<Sprite>(entity, &ecsManager->GetComponent<Transform>(entity), "../data/mrkrabs.png", Vec2(0.5f));
        ecsManager->AddComponent<Collider>(entity, &ecsManager->GetComponent<Transform>(entity), ColliderShape::RECT, Vec2(0.5f));
        
        trs = &ecsManager->GetComponent<Transform>(entity);
        trs->scale = { 1.0f, 1.0f };

        sprite = &ecsManager->GetComponent<Sprite>(entity);
        coll = &ecsManager->GetComponent<Collider>(entity);
        coll->m_Size = sprite->getImageSize();

        //sprite = new Sprite();
        //std::string x("../data/safe.xml");
        //Sprite::Load(x, *sprite);
    }

    void Engine::Run(){

        SetUp();

        const float mustDelta = (1.0f / fps);
        float initTime = tigrTime();
        float prevFrameTime= 0.0f;

        while (m_bIsRunning) {

            initTime += tigrTime();
            if (initTime - prevFrameTime < mustDelta) {
                float elpased= Wait((mustDelta - (initTime - prevFrameTime)) * 1000.0f);
                initTime += elpased;
            }
            m_deltaTime = initTime - prevFrameTime;
            prevFrameTime = initTime;

            Update();
        }
    }

    bool Engine::Quit(){
        //to do:: QUITAR
            //std::string x("../data/safe.xml");
            //Sprite::Save(x, *sprite);
            //delete sprite;
        //to do:: QUITAR

        ecsManager->Close(); //CERRAR MANAGER

        tigrFree(m_screen); // ELIMINAR MAIN WINDOW
        m_screen = nullptr;

        return true;
    }

    bool Engine::getIsRunning() const{
        return m_bIsRunning;
    }

    void Engine::printText(Tigr* screen, const std::string& text, Vec2 pos)
    {
        tigrPrint(screen, tfont, (int)pos.x, (int)pos.y, tigrRGB(0xff, 0xff, 0xff), text.c_str());
    }

    void Engine::Input() {
        m_bIsRunning = !tigrClosed(m_screen) && !tigrKeyDown(m_screen, TK_ESCAPE);

        //if (!tigrClosed(m_screen) && tigrKeyHeld(m_screen, TK_RIGHT)) {
        //    //sprite->setPosition(sprite->getPosition() + Vec2(10, 0));
        //}
        //if (!tigrClosed(m_screen) && tigrKeyHeld(m_screen, TK_LEFT)) {
        //    //sprite->setPosition(sprite->getPosition() + Vec2(-10, 0));
        //}
        //if (!tigrClosed(m_screen) && tigrKeyHeld(m_screen, TK_UP)) {
        //    //sprite->setPosition(sprite->getPosition() + Vec2(0, -10));
        //}
        //if (!tigrClosed(m_screen) && tigrKeyHeld(m_screen, TK_DOWN)) {
        //    //sprite->setPosition(sprite->getPosition() + Vec2(0, 10));
        //}
    }

    void Engine::Update(){
        Input();
        ecsManager->UpdateSystems(m_deltaTime);
    }

    float Engine::Wait(float ms){
        float totalTimeWaited = 0.0f;
        while (ms > totalTimeWaited * 1000.0f) {
            totalTimeWaited += tigrTime();
        }

        return totalTimeWaited;
    }

    void Engine::logme(const std::string& text) {
        std::cout << text << "\n";
    }
}