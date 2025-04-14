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

                auto it = componentFactory.find(componentName);
                if (it != componentFactory.end()) {
                    it->second(e, componentNode);
                }
                else {
                    std::cerr << "No factory registered for component: " << componentName << std::endl;
                }
            }
        }
    }
    std::vector<Entity>& ReadFilesSystem::ReadPrefabs(const std::string& xml_file){
        std::vector<Entity> prefabs;

        pugi::xml_document doc;
        if (!doc.load_file(xml_file.c_str())) {
            std::cerr << "Error loading XML file: " << xml_file << std::endl;
            return  prefabs;
        }

        pugi::xml_node root = doc.child("Entities");
        for (pugi::xml_node entityNode : root.children("Entity")) {
            Entity e = m_ecsManager->CreateEntity();

            // Recorremos los hijos que son componentes
            for (pugi::xml_node componentNode : entityNode.children()) {
                std::string componentName = componentNode.name();

                auto it = componentFactory.find(componentName);
                if (it != componentFactory.end()) {
                    it->second(e, componentNode);
                }
                else {
                    std::cerr << "No factory registered for component: " << componentName << std::endl;
                }
            }
            prefabs.push_back(e);
        }

        return prefabs;
    }
}