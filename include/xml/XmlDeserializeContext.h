//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XMLDESERIALIZECONTEXT_H
#define XML_DEMON_XMLDESERIALIZECONTEXT_H
#include "xml/Xml.h"
#include "xml/XmlObject.h"


/**
 * Класс предназначеный для оргниации иерархии сериализаторов.
 * Одна сущность может в себе содержать множество других сущностей. Десериализатор конкретной сущности не обязан
 * выполнять разбор вложенных сущностей, он может возложить эту обязанность на соответсвующие десериализаторы. Через
 * данный объект текущий десериализатор может попростить выполнить десериализацию вложенных сущностей.
 */
class XmlDeserializeContext {
public:
    /**
     *
     * @param instance - указатель на контейнер сериализаторов
     * @param document - указатель на корневой элемент всего документа
     * @param node - указатель на корень сущности
     */
    XmlDeserializeContext(Xml *instance, const Parser::XmlGraph::Iterator& document,const Parser::XmlGraph::Iterator& node);

    /**
     * Десериализация вложенной сущности другим десериализатором.
     * @tparam T - класс сущности, в который выоплняется десериализатор.
     * @param obj - описатель сущности.
     * @return десериализованная сущность.
     */
    template<typename T>
    T deserialize(XmlObject &obj) {
        std::shared_ptr<XmlSerializer<T>> ptr =  mContext->getSerializer<T>();
        if(ptr) {
            return ptr->deserialize(std::make_unique<XmlDeserializeContext>(mContext, mDocument, obj.mItr));
        }
        //TODO исключение об остуствии зарегистрированного обработчика
    }
    /**
     * @brief получить описатель сущности по названию тега  xml формата.
     * @param name - название тега.
     * @return описатель сущности.
     */
    Optional<XmlObject> get(const std::string &name);
private:
    Parser::XmlGraph::Iterator mDocument;
    Parser::XmlGraph::Iterator mNode;
    Xml *mContext{};
};

#endif //XML_DEMON_XMLDESERIALIZECONTEXT_H
