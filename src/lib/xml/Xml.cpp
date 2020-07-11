#include "xml/XmlDeserializeContext.h"

XmlDeserializeContext::XmlDeserializeContext(Xml *instance, const Parser::XmlGraph::Iterator& document,
                                             const Parser::XmlGraph::Iterator& node)
: mContext(instance), mDocument(document), mNode(node)
{}

Optional<XmlObject>  XmlDeserializeContext::get(const std::string &name) {
    if((*mNode)->name == name) {
        return XmlObject(mNode);
    }
    return {XmlObject(Parser::XmlGraph::Iterator()), false};
}
