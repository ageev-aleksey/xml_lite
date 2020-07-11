#ifndef XML_DEMON_TABLESERIALIZER_H
#define XML_DEMON_TABLESERIALIZER_H
#include "xml/XmlSerializer.h"
#include "xml/XmlObject.h"
#include "entity/Table.h"

class TableSerializer : public XmlSerializer<Table> {
public:
    std::string serialize(Table object) override ;
    Table deserialize(std::unique_ptr<XmlDeserializeContext> context) override;
};



#endif //XML_DEMON_TABLESERIALIZER_H
