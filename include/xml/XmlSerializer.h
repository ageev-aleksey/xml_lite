//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XMLSERIALIZER_H
#define XML_DEMON_XMLSERIALIZER_H
#include <string>
#include <memory>

class XmlDeserializeContext;

class BaseXmlSerializer {
public:
    virtual ~BaseXmlSerializer() = default;
};

/**
 * @brief Интерфейс сериализатора.
 * @tparam T - тип для которого выполнятеся сериализация и десериализация.
 */
template <typename T>
class XmlSerializer : public BaseXmlSerializer {
public:
    /**
     * Функционал не реализован
     * @param object
     * @return
     */
    virtual std::string serialize(T object) = 0;
    /**
     * @brief Метод для десериализации объекта
     * @param context - контекст сериализатора
     * @return десериализованный объект
     */
    virtual T deserialize(std::unique_ptr<XmlDeserializeContext> context) = 0;
    virtual ~XmlSerializer() override = default;
};

#endif //XML_DEMON_XMLSERIALIZER_H
