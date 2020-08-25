#pragma once
#ifndef __JSONOBJECT_HPP__
#define __JSONOBJECT_HPP__

#include <cctype>
#include <cstdint>
#include <fstream>
#include <string>
#include <sstream>
#include <list>

class JsonObject;

enum class ObjType : uint8_t { ERROR, INT, BOOL, STR, DOUBLE, NUL, LIST, DICT };

union ObjPtr {
    int* _int;
    bool* _bool;
    double* _double;
    std::string* _str;
    std::list<JsonObject*>* _list;
    std::list<std::pair<JsonObject*, JsonObject*>>* _dict;
};

class JsonObject {
private:
    ObjType _type = ObjType::ERROR;
    ObjPtr _ptr;

protected:
    static inline std::size_t countDigit(const std::string&, std::size_t);
    static inline std::size_t countCharacter(const std::string&, std::size_t);
    static inline char parseEscapeCharacter(const char&);
    bool parse(const std::string&, std::size_t&);
    static bool parseNumber(JsonObject*, const std::string&, std::size_t&);
    static bool parseEtc(JsonObject*, const std::string&, std::size_t&);
    static bool parseString(JsonObject*, const std::string&, std::size_t&);
    static bool parseList(JsonObject*, const std::string&, std::size_t&);
    static bool parseDict(JsonObject*, const std::string&, std::size_t&);
    static JsonObject* generateJsonObject(const int&);
    static JsonObject* generateJsonObject(const double&);
    static JsonObject* generateJsonObject(const std::string&);

public:
    ~JsonObject();
    JsonObject();
    JsonObject(const JsonObject&);
    JsonObject(const std::string&);
    std::string type() const;
    int toInt() const;
    bool toBool() const;
    std::string toString() const;
    double toDouble() const;
    int& getInt();
    bool& getBool();
    std::string& getString();
    double& getDouble();
    operator int() const;
    operator bool() const;
    operator std::string() const;
    operator double() const;
    int& operator=(const int&);
    bool& operator=(const bool&);
    std::string& operator=(const std::string&);
    double& operator=(const double&);
    JsonObject& operator[](const int&);
    JsonObject& operator[](const double&);
    JsonObject& operator[](const std::string&);
    bool empty() const;
    std::size_t size() const;
    void clear();
    static JsonObject& loads(const std::string&);
    static JsonObject& load(const std::string&);
    static std::string dumps(const JsonObject&);
    static bool dump(const std::string&, const JsonObject&);
};

JsonObject& operator""_json(const char*, std::size_t);

#endif // !__JSONOBJECT_HPP__