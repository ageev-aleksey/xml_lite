#include "entity/TableSerializer.h"
#include "xml/XmlDeserializeContext.h"

std::string TableSerializer::serialize(Table object) {
    return "";
}

Table TableSerializer::deserialize(std::unique_ptr<XmlDeserializeContext> context) {
    Optional<XmlObject> table = context->get("Table");
    if(table) {
        std::list<XmlObject> ptList = table->asList("param_text");
        if(ptList.empty()) {
            return {};
        }
        Table res;
        for(auto &el : ptList) {
            res.users.push_back(context->deserialize<ParamText>(el));
        }
        return res;
    }
    throw std::runtime_error("invalid format xml: not found Table entity");

}