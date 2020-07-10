//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XMLOBJECT_H
#define XML_DEMON_XMLOBJECT_H


#include "xml/Parser.h"
#include <optional>

class XmlDeserializeContext;
/**
 * \brief класс описывающий объект в xml формате
 */
class XmlObject {
public:
    explicit XmlObject(const Parser::XmlGraph::Iterator &root);
    ~XmlObject() = default;
    /**
     * Возвращет объект, по названию тега. Если текущий описатель содержит список таких объектов, то метод
     * будет всегда возвращать первый эелемент. Если необходимо получить и другие элементы, то необходимо воспользоваться
     * методом \see asList.
     * @param name
     * @return
     */
    std::optional<XmlObject> get(std::string name);
    /**
     * \brief возвращает список XmlObject по имени.
     *
     * Например если имеется следующая структура:
     * <nodes>
     *   <node></node>
     *   <node></node>
     * </nodes>
     * и текущий объект является описателем объекта <nodes></nodes>, то для того, чтобы получить все вложенные объекты
     * <node></nodes> необхожимо вызвать метод asList("node") на текущем объекте-описателе
     * @param name
     * @return
     */
    std::list<XmlObject> asList(std::string name);
    /**
     * \brief Десериализация из xml объетка, который содержит данный описатель.
     *
     * Перед вызовом данного метода необходимо, чтобы десериализатор для объетка T был зарегистрирован.
     *
     * @tparam T тип объетка, который описавается текущим описателем.
     * @return - объект типа T содержащий поля, которые были представленн в xml и были обработаны десериализатором.
     */
//    template<typename T>
//    T as() {
//
//    }

    /**
     * \brief Извлечение текста из тела xml тега, который представлен данным описателем
     * @return текст из тела xml тега
     */
    std::list<std::string> getText();
    /**
     * \brief Возвращает
     * @param name
     * @return
     */
    std::optional<std::string> property(const std::string &name);

    friend class Xml;
    friend class XmlDeserializeContext;
private:
    std::shared_ptr<XmlDeserializeContext> mContext{};
    Parser::XmlGraph::Iterator mItr;
};
#endif //XML_DEMON_XMLOBJECT_H
