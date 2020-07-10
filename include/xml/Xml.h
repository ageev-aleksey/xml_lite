//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XML_H
#define XML_DEMON_XML_H
#include "xml/XmlSerializer.h"
#include "Parser.h"
#include <unordered_map>

class XmlDeserializeContext;

class Xml {
public:
    template<typename T>
    void addSerializer(std::shared_ptr<XmlSerializer<T>> serializer) {
        serializers.insert({typeid(T).hash_code(), serializer});
    }


    template<typename T>
    T deserialize(const std::string &str) {

        std::shared_ptr<XmlSerializer<T>> serializer = getSerializer<T>();
        if(serializer) {
            Parser parser((Lexer(str)));
            Parser::XmlGraph g = parser.parse();
            auto documentNodeItr = g.begin();
            auto rootNodeItr = *documentNodeItr.getChildren().begin();
            return serializer->deserialize(std::make_unique<XmlDeserializeContext>(this, documentNodeItr, rootNodeItr));
        } //TODO исключение при условии, что соответсвующий десериализатор не зарегистрирован
        else {
            throw std::runtime_error(std::string("deserializer for ") + typeid(T).name() + "not found");
        }

    }
    template<typename T>
    T deserialize(const Parser::XmlGraph::Iterator &itr) {
        std::shared_ptr<XmlSerializer<T>> serializer = getSerializer<T>();
        if(serializer) {
           // serializer->deserialize(DeserializeContext(this, itr));
        }//TODO исключение при условии, что соответсвующий десериализатор не зарегистрирован
        throw std::runtime_error(std::string("deserializer for ") + typeid(T).name() + "not found");
    }
    friend class XmlDeserializeContext;
private:
    template<typename T>
    std::shared_ptr<XmlSerializer<T>> getSerializer() {
        size_t hash = typeid(T).hash_code();
        auto ptr = serializers.find(hash);
        if(ptr != serializers.end()) {
            return std::static_pointer_cast<XmlSerializer<T>>(ptr->second);
        }
        return nullptr;
    }

    std::unordered_map<size_t, std::shared_ptr<BaseXmlSerializer>> serializers;

};




#endif //XML_DEMON_XML_H
