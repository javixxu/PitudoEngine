#include "Engine.h"
#include <iostream>

#include <tigr/tigr.h>
#include <ecs/ECSManager.h>

#include "Vec2.h"

#include "GameManagerSystem.h"
#include "ReadFilesSystem.h"
#include "InputSystem.h"
#include "ColliderSystem.h"
#include "RenderSystem.h"
#include "RenderDebugSystem.h"

//GAME
#include "PlayersSystem.h"
#include "PlayerController.h"
#include "EnemySystem.h"
#include "Enemy.h"
#include "ScoreSystem.h"
//GAME

#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"


namespace PitudoEngine {
    bool Engine::Init(){
        m_bIsRunning = true;

        std::srand(static_cast<unsigned>(std::time(nullptr))); // Inicializar semilla

        m_screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PitudoEngine", 0);
        std::cout << "Initializing Tiger\n";
       
        ecsManager = &ECSManager::getInstance();
        ecsManager->Init();

        return !!m_screen;// conv a explicito
    }

    void Engine::SetUp(){

        //REGISTER AND INIT SYSTEMS
        RegisterSystems();

        //REGISTER COMPONENTS
        RegisterComponents();
        
        //SIGNATURES
        SetSignatures();

        //LOAD SCENE
        auto readfilesystem = &ecsManager->GetSystem<ReadFilesSystem>();
        readfilesystem->ReadSceneXML("../data/Scene.xml");

        //BORDER COLLIDERS
        CreateBorders();

        //LOAD ENEMYS PREFABS
        auto enemySystem = &ecsManager->GetSystem<SuperPangGame::EnemySystem>();
        enemySystem->SetEnemyPrefabs(readfilesystem->ReadPrefabs("../data/prefabs/EnemyPrefabs.xml"));

        ecsManager->GetSystem<ColliderSystem>().AddIgnoreLayers("enemy", "enemy");
        ecsManager->GetSystem<SuperPangGame::ScoreSystem>().Init("../data/scores.txt");
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

        ecsManager->Close(); //CERRAR MANAGER

        tigrFree(m_screen); // ELIMINAR MAIN WINDOW
        m_screen = nullptr;

        return true;
    }

    bool Engine::getIsRunning() const{
        return m_bIsRunning;
    }

    void Engine::printText(Tigr* screen, const std::string& text, Vec2 pos,TPixel color)
    {
        tigrPrint(screen, tfont, (int)pos.x, (int)pos.y, color, text.c_str());
    }

    void Engine::Update(){
        //TO DO:: QUITAR
        m_bIsRunning = !tigrClosed(m_screen) && !tigrKeyDown(m_screen, TK_ESCAPE);
        //TO DO:: QUITAR

        ecsManager->GetSystem<InputSystem>().Update(m_deltaTime);

        ecsManager->GetSystem<GameManagerSystem>().Update(m_deltaTime);

        ecsManager->GetSystem<SuperPangGame::PlayersSystem>().Update(m_deltaTime);
        ecsManager->GetSystem<SuperPangGame::EnemySystem>().Update(m_deltaTime);

        ecsManager->GetSystem<ColliderSystem>().Update(m_deltaTime);

        ecsManager->GetSystem<SuperPangGame::ScoreSystem>().Update(m_deltaTime);

        ecsManager->GetSystem<GameManagerSystem>().CleanEntities();

        ecsManager->GetSystem<RenderSystem>().Update(m_deltaTime);
    #ifdef _DEBUG
        ecsManager->GetSystem<RenderDebugSystem>().Update(m_deltaTime);
    #endif
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

    void Engine::CreateBorders(){
        const float BORDER_THICKNESS = 10.0f;
        std::string layer = "border";
        // Crear borde superior
        Entity topBorder = ecsManager->CreateEntity();
        ecsManager->AddComponent<Transform>(topBorder, Vec2(SCREEN_WIDTH / 2, BORDER_THICKNESS / 2), Vec2(1, 1), 0.0f);
        ecsManager->AddComponent<Collider>(topBorder, &ecsManager->GetComponent<Transform>(topBorder),
            ColliderShape::RECT, Vec2(0.5f), Vec2(SCREEN_WIDTH, BORDER_THICKNESS), layer);

        // Crear borde inferior
        Entity bottomBorder = ecsManager->CreateEntity();
        ecsManager->AddComponent<Transform>(bottomBorder, Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - BORDER_THICKNESS / 2), Vec2(1, 1), 0.0f);
        ecsManager->AddComponent<Collider>(bottomBorder, &ecsManager->GetComponent<Transform>(bottomBorder), 
            ColliderShape::RECT, Vec2(0.5f), Vec2(SCREEN_WIDTH, BORDER_THICKNESS), layer);

        // Crear borde izquierdo
        Entity leftBorder = ecsManager->CreateEntity();
        ecsManager->AddComponent<Transform>(leftBorder, Vec2(BORDER_THICKNESS / 2, SCREEN_HEIGHT / 2), Vec2(1, 1), 0.0f);
        ecsManager->AddComponent<Collider>(leftBorder, &ecsManager->GetComponent<Transform>(leftBorder), 
            ColliderShape::RECT, Vec2(0.5f), Vec2(BORDER_THICKNESS, SCREEN_HEIGHT), layer);

        // Crear borde derecho
        Entity rightBorder = ecsManager->CreateEntity();
        ecsManager->AddComponent<Transform>(rightBorder, Vec2(SCREEN_WIDTH - BORDER_THICKNESS / 2, SCREEN_HEIGHT / 2), Vec2(1, 1), 0.0f);
        ecsManager->AddComponent<Collider>(rightBorder, &ecsManager->GetComponent<Transform>(rightBorder), 
            ColliderShape::RECT, Vec2(0.5f), Vec2(BORDER_THICKNESS, SCREEN_HEIGHT), layer);

        ecsManager->GetSystem<ColliderSystem>().AddIgnoreLayers(layer, layer);
    }
   
    void Engine::SetSignatures(){
        //SIGNATURES
        Signature signatureRenderSystem;
        signatureRenderSystem.set(ecsManager->GetComponentType<Transform>());
        signatureRenderSystem.set(ecsManager->GetComponentType<Sprite>());
        ecsManager->SetSystemSignature<RenderSystem>(signatureRenderSystem);

        Signature signatureRenderDebugSystem;
        signatureRenderDebugSystem.set(ecsManager->GetComponentType<Transform>());
        signatureRenderDebugSystem.set(ecsManager->GetComponentType<Collider>());
        ecsManager->SetSystemSignature<RenderDebugSystem>(signatureRenderDebugSystem);

        Signature signatureCollider;
        signatureCollider.set(ecsManager->GetComponentType<Transform>());
        signatureCollider.set(ecsManager->GetComponentType<Collider>());
        ecsManager->SetSystemSignature<ColliderSystem>(signatureCollider);

        Signature signaturePlayerSystem;
        signaturePlayerSystem.set(ecsManager->GetComponentType<Transform>());
        signaturePlayerSystem.set(ecsManager->GetComponentType<SuperPangGame::PlayerController>());
        ecsManager->SetSystemSignature<SuperPangGame::PlayersSystem>(signaturePlayerSystem);

        Signature signatureEnemySystem;
        signatureEnemySystem.set(ecsManager->GetComponentType<Transform>());
        signatureEnemySystem.set(ecsManager->GetComponentType<SuperPangGame::Enemy>());
        signatureEnemySystem.set(ecsManager->GetComponentType<Collider>());
        signatureEnemySystem.set(ecsManager->GetComponentType<Sprite>());
        ecsManager->SetSystemSignature<SuperPangGame::EnemySystem>(signatureEnemySystem);
    }
   
    void Engine::RegisterSystems(){

        auto gameManager = ecsManager->RegisterSystem<GameManagerSystem>();

        auto readFilesSystem = ecsManager->RegisterSystem<ReadFilesSystem>(); //Registrar todos los componenets k tengan que ser leidos

        auto inputSystem = ecsManager->RegisterSystem<InputSystem>();
        inputSystem->setContext(m_screen);

        auto playersSystem = ecsManager->RegisterSystem<SuperPangGame::PlayersSystem>();

        auto enemysSystem = ecsManager->RegisterSystem<SuperPangGame::EnemySystem>();


        auto colliderSystem = ecsManager->RegisterSystem<ColliderSystem>();

        auto renderSystem = ecsManager->RegisterSystem<RenderSystem>();
        renderSystem->setContext(m_screen);

    #ifdef _DEBUG
        auto renderDebugSystem = ecsManager->RegisterSystem<RenderDebugSystem>();
        renderDebugSystem->setContext(m_screen);
    #endif
        auto scoreSystem = ecsManager->RegisterSystem<SuperPangGame::ScoreSystem>();
    }

    void Engine::RegisterComponents(){

        auto readFilesSystem = &ecsManager->GetSystem<ReadFilesSystem>();

        ecsManager->RegisterComponent<Transform>();
        readFilesSystem->RegisterComponent<Transform>("Transform");

        ecsManager->RegisterComponent<Sprite>();
        readFilesSystem->RegisterComponent<Sprite>("Sprite");

        ecsManager->RegisterComponent<Collider>();
        readFilesSystem->RegisterComponent<Collider>("Collider");

        // TO DO:: QUITAR
        ecsManager->RegisterComponent<SuperPangGame::PlayerController>();
        readFilesSystem->RegisterComponent<SuperPangGame::PlayerController>("PlayerController");

        ecsManager->RegisterComponent<SuperPangGame::Enemy>();
        readFilesSystem->RegisterComponent<SuperPangGame::Enemy>("Enemy");
    }

    int Engine::getWidth()
    {
        return SCREEN_WIDTH;
    }

    int Engine::getHeight()
    {
        return SCREEN_HEIGHT;
    }
}