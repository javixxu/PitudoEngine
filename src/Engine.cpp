#include "Engine.h"

#include <tigr.h>
#include <iostream>

namespace PitudoEngine {
    bool Engine::Init(){
        m_bIsRunning = true;
        screen = tigrWindow(320, 240, "Hello", 0);
        return !!screen;// conv a explicito
    }

    void Engine::Run(){
        while (m_bIsRunning) {
            //Input & Logica & Collisiones
            Update();

            //Renderizado
            Render();
        }
    }

    bool Engine::Quit(){
        tigrFree(screen);
        screen = nullptr;
        return true;
    }

    void Engine::Input(){
        m_bIsRunning = !tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE);
    }

    void Engine::Update(){
        //Input
        Input();

        //Logica

        //Collisiones

    }
    void Engine::Render(){
        //CLEAR BUFFER
        tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0)); 

        //CONTENT QUE RENDERIZAR
        //tigrPrint(screen, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff), "Hello, world.");

        //ACTUALIZAR BUFFER
        tigrUpdate(screen);
    }

    void Engine::logme(const std::string& text) {
        std::cout << text << "\n";
    }

    void Engine::logme(const char* text) {
        puts(text);
    }
}