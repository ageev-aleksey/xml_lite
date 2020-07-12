//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XMLOBJECT_H
#define XML_DEMON_XMLOBJECT_H


#include "xml/Parser.h"
#include "xml/util/Optional.h"

#include <experimental/optional>
class XmlDeserializeContext;
/**
 * \brief Класс описывающий объект в xml формате.
 */
class XmlObject {
public:
    explicit XmlObject(const Parser::XmlGraph::Iterator &root);
    ~XmlObject() = default;
    /**
     * Возвращет объект, по названию тега. Если текущий описатель содержит список таких объектов, то метод
     * будет всегда возвращать первый элемент. Если необходимо получить и другие элементы, то необходимо воспользоваться
     * методом \see asList.
     * @param name
     * @return
     */
    Optional<XmlObject> get(std::string name);
    /**
     * @brief Возвращает список XmlObject по имени.
     *
     * Например если имеется следующая структура:
     * <nodes>
     *   <node></node>
     *   <node></node>
     * </nodes>
     * и текущий объект является описателем объекта <nodes></nodes>, то для того, чтобы получить все вложенные объекты
     * <node></nodes> необхожимо вызвать метод asList("node") на текущем объекте-описателе
     * @param name - названеи тега.
     * @return Список описателей.
     */
    std::list<XmlObject> asList(std::string name);

    /**
     * \brief Извлечение текста из тела xml тега, который представлен данным описателем
     * @return текст из тела xml тега
     */
    std::list<std::string> getText();
    /**
     * \brief Возвращает значение указанного свойсвта.
     * @param name - название свойства.
     * @return значение свойства.
     */
    Optional<std::string> property(const std::string &name);

    friend class Xml;
    friend class XmlDeserializeContext;
private:
    std::shared_ptr<XmlDeserializeContext> mContext{};
    Parser::XmlGraph::Iterator mItr;
};
#endif //XML_DEMON_XMLOBJECT_H
