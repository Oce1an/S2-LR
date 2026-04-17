#include "component.h"
#include <sstream>

const std::string ComponentTypes::CPU = "CPU";
const std::string ComponentTypes::GPU = "GPU";
const std::string ComponentTypes::MOTHERBOARD = "Motherboard";
const std::string ComponentTypes::RAM = "RAM";
const std::string ComponentTypes::STORAGE = "Storage";
const std::string ComponentTypes::PSU = "PSU";

std::vector<std::string> ComponentTypes::getAllTypes() {
    return {CPU, GPU, MOTHERBOARD, RAM, STORAGE, PSU};
}

bool ComponentTypes::isValidType(const std::string& type) {
    std::vector<std::string> types = getAllTypes();
    return std::find(types.begin(), types.end(), type) != types.end();
}

Component::Component()
    : type(""), manufacturer(""), model(""), parameters(""), price(0.0), inStock(false) {}

Component::Component(const std::string& type, const std::string& manufacturer,
                     const std::string& model, const std::string& parameters,
                     double price, bool inStock)
    : type(type), manufacturer(manufacturer), model(model),
    parameters(parameters), price(price), inStock(inStock) {}

std::string Component::toString() const {
    std::stringstream ss;
    ss << type << "|" << manufacturer << "|" << model << "|"
       << parameters << "|" << price << "|" << (inStock ? "1" : "0");
    return ss.str();
}

Component Component::fromString(const std::string& str) {
    std::stringstream ss(str);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() >= 6) {
        return Component(tokens[0], tokens[1], tokens[2], tokens[3],
                         std::stod(tokens[4]), tokens[5] == "1");
    }
    return Component();
}
