#pragma once
#include <ecs/System.h>
namespace SuperPangGame {
	class ScoreSystem : public System
	{
		std::string m_RecordsFile;

		float m_CurrentScore;
		float m_BestScore;
	public:
		ScoreSystem();
		~ScoreSystem();

		void Init(std::string _recordsFile);

		void Update(float deltaTime) override;
		void Reset() override;

		void TrySetRecord();

		const float GetCurrentScore() const;
		const float GetRecordScore() const;

		void ReadFile();
		void SaveBestRecord();
	};
}
