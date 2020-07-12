//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XML_H
#define XML_DEMON_XML_H
#include "xml/exception/XmlParseError.h"
#include "xml/XmlSerializer.h"
#include "Parser.h"
#include <unordered_map>

class XmlDeserializeContext;

/**
 * Контейнер сериализаторов для формата Xml. При сериализации и десериализации ищет соотвествующий класс сериализатор.
 * Объекты классов сериализаторов предварительно должны быть добавлены в контейнер.
 */
class Xml {
public:
    /**
     * Добавление объекта класса выполняющий сериализацию объекта типа Т
     * @tparam T - тип объетка, для которого предназначен добавляемый сериализатор
     * @param serializer
     */
    template<typename T>
    void addSerializer(std::shared_ptr<XmlSerializer<T>> serializer) {
        serializers.insert({typeid(T).hash_code(), serializer});
    }

    /**
     * \brief Десериализация объекта типа Т
     *
     * Перед вызовом данного метода соответсвующий объект-сериализатор должен быть добавлен в контейнер
     * @tparam T - тип объекта который сериализуется из xml формата
     * @param str - строка содержащая объект типа T в формате xml
     * @throw XmlParserError Если в контейнере отсутсвует соответствующий сериализатор
     * @return десериализованный объект
     */
    template<typename T>
    T deserialize(const std::string &str) {

        std::shared_ptr<XmlSerializer<T>> serializer = getSerializer<T>();
        if(serializer) {
            Parser parser((Lexer(str)));
            Parser::XmlGraphPtr g = parser.parse();
            auto documentNodeItr = g->begin();
            auto rootNodeItr = *documentNodeItr.getChildren().begin();
            return serializer->deserialize(std::make_unique<XmlDeserializeContext>(this, documentNodeItr, rootNodeItr));
        }
        else {
            throw XmlParserError(std::string("deserializer for ") + typeid(T).name() + "not found");
        }

    }
//    template<typename T>
//    T deserialize(const Parser::XmlGraph::Iterator &itr) {
//        std::shared_ptr<XmlSerializer<T>> serializer = getSerializer<T>();
//        if(serializer) {
//           // serializer->deserialize(DeserializeContext(this, itr));
//        }//
//        throw XmlParserError(std::string("deserializer for ") + typeid(T).name() + "not found");
//    }
    friend class XmlDeserializeContext;
private:
    template<typename T>
    std::shared_ptr<XmlSerializer<T>> getSerializer() {
        static const size_t hash = typeid(T).hash_code();
        auto ptr = serializers.find(hash);
        if(ptr != serializers.end()) {
            return std::static_pointer_cast<XmlSerializer<T>>(ptr->second);
        }
        return nullptr;
    }

    std::unordered_map<size_t, std::shared_ptr<BaseXmlSerializer>> serializers;

};




#endif //XML_DEMON_XML_H
