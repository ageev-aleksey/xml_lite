#include "xml/exception/XmlParseError.h"

XmlParserError::XmlParserError(const std::string &msg) : std::runtime_error(msg) {}