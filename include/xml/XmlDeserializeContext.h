//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XMLDESERIALIZECONTEXT_H
#define XML_DEMON_XMLDESERIALIZECONTEXT_H
#include "xml/Xml.h"
#include "xml/XmlObject.h"


class XmlDeserializeContext {
public:
    XmlDeserializeContext(Xml *instance, const Parser::XmlGraph::Iterator& document,const Parser::XmlGraph::Iterator& node);
    template<typename T>
    T deserialize(XmlObject &obj) {
        std::shared_ptr<XmlSerializer<T>> ptr =  mContext->getSerializer<T>();
        if(ptr) {
            return ptr->deserialize(std::make_unique<XmlDeserializeContext>(mContext, mDocument, obj.mItr));
        }
        //TODO исключение об остуствии зарегистрированного обработчика
    }
    std::optional<XmlObject> get(const std::string &name);
private:
    Parser::XmlGraph::Iterator mDocument;
    Parser::XmlGraph::Iterator mNode;
    Xml *mContext{};
};

#endif //XML_DEMON_XMLDESERIALIZECONTEXT_H
