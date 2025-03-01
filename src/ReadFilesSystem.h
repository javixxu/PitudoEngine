#pragma once

#include <string>
#include <variant>



using ComponentValue = std::variant<int, float, std::string>;

class ReadFilesSystem{
	static void ReadXML(const std::string& xml_file);
};

