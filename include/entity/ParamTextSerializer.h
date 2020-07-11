//
// Created by nrx on 11.07.2020.
//

#ifndef XML_DEMON_PARAMTEXTSERIALIZER_H
#define XML_DEMON_PARAMTEXTSERIALIZER_H
#include "xml/XmlSerializer.h"
#include "xml/XmlObject.h"
#include "entity/ParamText.h"

class ParamTextSerializer : public XmlSerializer<ParamText> {
    std::string serialize(ParamText object) override;
    ParamText deserialize(std::unique_ptr<XmlDeserializeContext> context) override;
};


#endif //XML_DEMON_PARAMTEXTSERIALIZER_H
