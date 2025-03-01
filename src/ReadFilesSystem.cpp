#include "ReadFilesSystem.h"
#include <pugixml/pugixml.hpp>
#include <map>
#include <iostream>
void ReadFilesSystem::ReadXML(const std::string& xml_file){
    pugi::xml_document doc;

    // Cargar el archivo XML
    if (!doc.load_file(xml_file.c_str())) {
        std::cerr << "Error loading XML file with Name: "<< xml_file << std::endl;
        return;
    }
    for (pugi::xml_node entityNode : doc.child("Entities").children("Entity")) {
        std::string tag = entityNode.attribute("tag").as_string();

        //TO DO:: CREAR ENTIDAD

        // Iterar sobre los componentes de la entidad (cada nodo hijo de la entidad es un componente)
        for (pugi::xml_node componentNode : entityNode.children()) {
            std::string componentName = componentNode.name();
            std::map<std::string, ComponentValue> componentValues;

            // Iterar sobre los atributos de cada componente
            for (pugi::xml_attribute attr : componentNode.attributes()) {
                std::string attributeName = attr.name();
                ComponentValue value;

                // Determinar el tipo de dato del atributo y almacenarlo en el mapa correspondiente
                if (attr.as_int() != 0 || attr.as_string()[0] == '0') {
                    value = attr.as_int();
                }
                else if (attr.as_float() != 0.0f) {
                    value = attr.as_float();
                }
                else {
                    value = attr.as_string();
                }

                componentValues[attributeName] = value;
            }

            // TO DO:: CREAR UN COMPOENENTE DEL TIPO Y ASOCIARLO CON LA ENTIDAD
        }
        
    }
}
