#include "ReadFilesSystem.h"
#include <iostream>

#include <ecs/ecsDefinitions.h>
namespace PitudoEngine {

    ReadFilesSystem::ReadFilesSystem(){
    }

    ReadFilesSystem::~ReadFilesSystem(){
    }

    void ReadFilesSystem::ReadSceneXML(const std::string& xml_file) {
        pugi::xml_document doc;
        if (!doc.load_file(xml_file.c_str())) {
            std::cerr << "Error loading XML file: " << xml_file << std::endl;
            return;
        }

        pugi::xml_node root = doc.child("Entities");
        for (pugi::xml_node entityNode : root.children("Entity")) {
            Entity e = m_ecsManager->CreateEntity();

            // Recorremos los hijos que son componentes
            for (pugi::xml_node componentNode : entityNode.children()) {
                std::string componentName = componentNode.name();

                std::unordered_map<std::string, std::string> values;
                for (const pugi::xml_attribute& attr : componentNode.attributes()) {
                    values[attr.name()] = attr.value();
                }

                auto it = componentFactory.find(componentName);
                if (it != componentFactory.end()) {
                    it->second(e, values);
                }
                else {
                    std::cerr << "No factory registered for component: " << componentName << std::endl;
                }
            }
        }
    }

    std::vector<PrefabData*> ReadFilesSystem::ReadPrefabs(const std::string& xml_file) {
        std::vector<PrefabData*> prefabs;
        pugi::xml_document doc;
        if (!doc.load_file(xml_file.c_str())) {
            std::cerr << "Error loading XML file: " << xml_file << std::endl;
            return prefabs;
        }

        pugi::xml_node root = doc.child("Entities");
        for (pugi::xml_node entityNode : root.children("Entity")) {
            std::string name = entityNode.attribute("name").as_string(); // cada prefab debe tener nombre
            PrefabData* data = new PrefabData();
            std::unordered_map<std::string, std::string> values;

            // Recorremos los componentes de cada entidad en el prefab
            for (pugi::xml_node componentNode : entityNode.children()) {
                std::string componentName = componentNode.name();

                auto it = componentFactory.find(componentName);
                if (it != componentFactory.end()) {

                    for (const pugi::xml_attribute& attr : componentNode.attributes()) {
                        values[attr.name()] = attr.value();
                    }
                    
                    data->componentConstructors.push_back([=](Entity e) {
                        it->second(e, data->values);
                        });
                }
            }
            data->values = values;

            prefabs.push_back(data); // Guardamos el prefab en el mapa
        }

        return prefabs;
    }
}