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
    class ReadFilesSystem :public System {

    public:
        ReadFilesSystem();
        ~ReadFilesSystem();

        template<typename T>
        void RegisterComponent(const std::string& name) {
            componentFactory[name] = [this](Entity e, const pugi::xml_node& node) {
                T comp;

                std::unordered_map<std::string, std::string> values;
                for (const pugi::xml_attribute& attr : node.attributes()) {
                    values[attr.name()] = attr.value();
                }

                comp.ReadData(values, e);
                m_ecsManager->AddComponent<T>(e, comp);
                };
        };

        void ReadSceneXML(const std::string& xml_file);
        std::vector<Entity>& ReadPrefabs(const std::string& xml_file);
    private:
        std::unordered_map<std::string, std::function<void(Entity, const pugi::xml_node&)>> componentFactory;
    };
}
