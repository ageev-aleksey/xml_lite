#include "entity/ParamTextSerializer.h"
#include "xml/XmlDeserializeContext.h"
ParamText ParamTextSerializer::deserialize(std::unique_ptr<XmlDeserializeContext> context) {
    Optional<XmlObject> paramText = context->get("param_text");
    ParamText pt;
    if(paramText) {
        pt.name = *paramText->get("name")->getText().begin();
        pt.date = *paramText->get("date")->getText().begin();
        pt.hoursWorked = std::stoi(*paramText->get("hours-worked")->getText().begin());
        std::string boolStr = *paramText->get("car-true")->getText().begin();
        if(boolStr == "YES") {
            pt.carTrue = true;
        } else if(boolStr == "NO") {
            pt.carTrue = false;
        } else {
            throw std::runtime_error("Invalid car-true format field in param_text entity");
        }
    }
    return pt;
}

std::string ParamTextSerializer::serialize(ParamText object) {
    return "";
}

