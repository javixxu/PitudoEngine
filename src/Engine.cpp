#include "Engine.h"
#include <iostream>

#include <tigr.h>
#include <ecs/ecs.h>
#include <pugixml/pugixml.hpp>

#include "Sprite.h"
#include "Vec2.h"

namespace PitudoEngine {
    bool Engine::Init(){
        m_bIsRunning = true;
        m_screen = tigrWindow(320, 240, "Hello", 0);
        std::cout << "Initializing Tiger\n";
        return !!m_screen;// conv a explicito
    }

    void Engine::SetUp(){
        sprite = new Sprite();
        std::string x("../data/safe.xml");
        Sprite::Load(x, *sprite);
       
       
    }

    void Engine::Run(){

        SetUp();

        const float mustDelta = (1.0f / fps);
        float initTime = tigrTime();
        float prevFrameTime= 0.0f;

        while (m_bIsRunning) {

            initTime += tigrTime();
            if (initTime - prevFrameTime < mustDelta) {
                float elpased= Wait((mustDelta - (initTime - prevFrameTime))*1000.0f);
                initTime += elpased;
            }
            m_deltaTime = initTime - prevFrameTime;
            prevFrameTime = initTime;

            //Input & Logica & Collisiones
            Update();

            //Renderizado
            Render();

        }
    }

    bool Engine::Quit(){
        //to do:: QUITAR
        std::string x("../data/safe.xml");
        Sprite::Save(x, *sprite);
        delete sprite;
        //to do:: QUITAR

        tigrFree(m_screen);
        m_screen = nullptr;
        return true;
    }

    bool Engine::getIsRunning() const{
        return m_bIsRunning;
    }

    void Engine::printText(const std::string& text,Vec2 pos)
    {
        tigrPrint(m_screen, tfont, (int)pos.x, (int)pos.y, tigrRGB(0xff, 0xff, 0xff), text.c_str());
    }

    void Engine::Input() {
        m_bIsRunning = !tigrClosed(m_screen) && !tigrKeyDown(m_screen, TK_ESCAPE);

        if (!tigrClosed(m_screen) && tigrKeyHeld(m_screen, TK_RIGHT)) {
            sprite->setPosition(sprite->getPosition() + Vec2(10, 0));
        }
        if (!tigrClosed(m_screen) && tigrKeyHeld(m_screen, TK_LEFT)) {
            sprite->setPosition(sprite->getPosition() + Vec2(-10, 0));
        }
        if (!tigrClosed(m_screen) && tigrKeyHeld(m_screen, TK_UP)) {
            sprite->setPosition(sprite->getPosition() + Vec2(0, -10));
        }
        if (!tigrClosed(m_screen) && tigrKeyHeld(m_screen, TK_DOWN)) {
            sprite->setPosition(sprite->getPosition() + Vec2(0, 10));
        }
    }

    void Engine::Update(){
        //Input
        Input();

        //Logica

        //Collisiones

    }
    void Engine::Render(){
        //CLEAR BUFFER
        tigrClear(m_screen, tigrRGB(0x80, 0x90, 0xa0)); 

        //CONTENT QUE RENDERIZAR
        sprite->Draw(m_screen);

        #ifdef _DEBUG
                RenderDebug();
        #endif // DEBUG

        //ACTUALIZAR BUFFER
        tigrUpdate(m_screen);
    }

    float Engine::Wait(float ms){
        float totalTimeWaited = 0.0f;
        while (ms > totalTimeWaited * 1000.0f) {
            totalTimeWaited += tigrTime();
        }

        return totalTimeWaited;
    }

    void Engine::RenderDebug(){
        printText("DeltaTime: " + sstr(m_deltaTime), {30,30});
        printText("FPS: " + sstr(1.0 / m_deltaTime), {30,45});
    }

    void Engine::logme(const std::string& text) {
        std::cout << text << "\n";
    }
}