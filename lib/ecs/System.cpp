#include "System.h"
#include "ECSManager.h"

System::System(){
	m_ecsManager = &ECSManager::getInstance();
}
