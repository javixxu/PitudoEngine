#pragma once
#include <ecs/System.h>
namespace SuperPangGame {
	class ScoreSystem : public System
	{
		std::string m_RecordsFile;

		float m_CurrentScore;
		float m_BestScore;

		ScoreSystem();
		~ScoreSystem();

		void Init(std::string _recordsFile);

		void Update(float deltaTime) override;

		bool IsBetterScore();

		const float GetCurrentScore() const;

		void ReadFile();
		void SaveBestRecord();
	};
}
