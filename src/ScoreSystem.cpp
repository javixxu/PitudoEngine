#include "ScoreSystem.h"
#include <ecs/ECSManager.h>

#include <fstream>
#include <iostream>
#include <limits>

#include "RenderSystem.h"
#include "Engine.h"

namespace SuperPangGame{
	ScoreSystem::ScoreSystem() :
		m_CurrentScore(0.0f),m_BestScore(INT_MIN) {
	}

	ScoreSystem::~ScoreSystem() {
	}

	void ScoreSystem::Init(std::string _recordsFile){
		m_RecordsFile = _recordsFile;

        ReadFile();//Leer Record

        auto* renderSystem = &m_ecsManager->GetSystem<PitudoEngine::RenderSystem>();

        renderSystem->addTextCallback([this]() {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "Score: %.2f", this->GetCurrentScore());
            return std::string(buffer);
        }, (float)(PitudoEngine::Engine::GetWidth() - 100), 20.0f, tigrRGB(255, 255, 255));
	}

	void ScoreSystem::Update(float deltaTime){

		m_CurrentScore += deltaTime;
	}

    void ScoreSystem::Reset(){
        m_CurrentScore = 0.0f;
    }

	void ScoreSystem::TrySetRecord() {
		m_BestScore = m_CurrentScore > m_BestScore ? m_CurrentScore: m_BestScore;
	}

    const float ScoreSystem::GetCurrentScore() const{
        return m_CurrentScore;
    }

    const float ScoreSystem::GetRecordScore() const
    {
        return m_BestScore;
    }

	void ScoreSystem::ReadFile(){
        std::fstream file(m_RecordsFile, std::ios::in | std::ios::out);

        if (!file) {
            // Si el archivo no existe, lo creamos con un valor inicial de 0
            std::cout << "Archivo no encontrado. Creando archivo..." << std::endl;
            file.open(m_RecordsFile, std::ios::out);
            if (file) {
                file << 0;
            }
            file.close();
            return;
        }

        // Si el archivo existe, leemos el best record
        file >> m_BestScore;

        if (file.fail()) {
            // Si la lectura falla, restablecemos el valor a 0
            std::cout << "Error al leer el archivo. Restableciendo a 0..." << std::endl;
            m_BestScore = 0.0f;
        }

        file.close();

        std::cout << "Best record actual: " << m_BestScore << std::endl;
	}

    void ScoreSystem::SaveBestRecord() {
        std::ofstream file(m_RecordsFile, std::ios::out | std::ios::trunc); // Abre en modo escritura, truncando el contenido

        if (!file) {
            std::cerr << "Error al abrir el archivo para escritura." << std::endl;
            return;
        }

        file << m_BestScore; // Escribimos el nuevo best record en el archivo
        file.close();

        std::cout << "Best record guardado: " << m_BestScore << std::endl;
    }
}