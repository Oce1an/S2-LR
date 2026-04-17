#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>
#include <algorithm>

class ComponentTypes {
public:
    static const std::string CPU;
    static const std::string GPU;
    static const std::string MOTHERBOARD;
    static const std::string RAM;
    static const std::string STORAGE;
    static const std::string PSU;

    static std::vector<std::string> getAllTypes();
    static bool isValidType(const std::string& type);
};

class Component {
private:
    std::string type;
    std::string manufacturer;
    std::string model;
    std::string parameters;
    double price;
    bool inStock;

public:
    Component();
    Component(const std::string& type, const std::string& manufacturer,
              const std::string& model, const std::string& parameters,
              double price, bool inStock);

    std::string getType() const { return type; }
    std::string getManufacturer() const { return manufacturer; }
    std::string getModel() const { return model; }
    std::string getParameters() const { return parameters; }
    double getPrice() const { return price; }
    bool getInStock() const { return inStock; }

    void setType(const std::string& t) { type = t; }
    void setManufacturer(const std::string& m) { manufacturer = m; }
    void setModel(const std::string& m) { model = m; }
    void setParameters(const std::string& p) { parameters = p; }
    void setPrice(double p) { price = p; }
    void setInStock(bool s) { inStock = s; }

    std::string toString() const;
    static Component fromString(const std::string& str);
};

#endif
