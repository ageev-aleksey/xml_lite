#include "xml/XmlDeserializeContext.h"

XmlDeserializeContext::XmlDeserializeContext(Xml *instance, const Parser::XmlGraph::Iterator& document,
                                             const Parser::XmlGraph::Iterator& node)
: mContext(instance), mDocument(document), mNode(node)
{}

std::optional<XmlObject>  XmlDeserializeContext::get(const std::string &name) {
    if((*mNode)->name == name) {
        return XmlObject(mNode);
    }
    return std::nullopt;
}
