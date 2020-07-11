#include "xml/XmlObject.h"


XmlObject::XmlObject(const Parser::XmlGraph::Iterator &root) : mItr(root)
{}

Optional<XmlObject> XmlObject::get(std::string name) {
    auto children = mItr.getChildren();
    for(Parser::XmlGraph::Iterator el : children) {
        if((*el)->name == name) {
            return XmlObject(el);
        }
    }
    return {XmlObject(Parser::XmlGraph::Iterator()), false};
}


std::list<XmlObject> XmlObject::asList(std::string name) {
    std::list<XmlObject> res;
    for(auto &el : mItr.getChildren()) {
        if((*el)->name == name) {
            res.emplace_back(el);
        }
    }
    return res;
}

std::list<std::string> XmlObject::getText() {
    std::list<std::string> res;
    for(auto &el : mItr.getChildren()) {
        XmlNode &n = **el;
        if(typeid(n) == typeid(XmlText)) {
            XmlText *tnode = dynamic_cast<XmlText*>(&n);
            if(tnode) {
                res.push_back(tnode->text);
            }
        }
    }
    return res;
}


Optional<std::string> XmlObject::property(const std::string &name) {
    auto &props = (*mItr)->props;
    auto itr = props.find(name);
    if(itr != props.end()) {
        return itr->second;
    }
    return {};
}