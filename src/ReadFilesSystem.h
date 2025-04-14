#pragma once

#include <string>
#include <variant>
#include <functional>

#include <unordered_map>
#include <string>

#include<pugixml/pugixml.hpp>

#include <ecs/System.h>
#include <ecs/ECSManager.h>

namespace PitudoEngine {

    struct PrefabData {
        std::unordered_map<std::string, std::string> values;
        std::vector<std::function<void(Entity)>> componentConstructors;
    };

    class ReadFilesSystem :public System {

    public:
        ReadFilesSystem();
        ~ReadFilesSystem();

        template<typename T>
        void RegisterComponent(const std::string& name) {
            componentFactory[name] = [this](Entity e, std::unordered_map<std::string, std::string> values) {
                T comp;

                comp.ReadData(values, e);
                m_ecsManager->AddComponent<T>(e, comp);
            };
        };

        void ReadSceneXML(const std::string& xml_file);
        std::vector<PitudoEngine::PrefabData*> ReadPrefabs(const std::string& xml_file);

    private:
        std::unordered_map<std::string, std::function<void(Entity, std::unordered_map<std::string, std::string>)>> componentFactory;
    };
}
