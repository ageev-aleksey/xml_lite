#include "xml/Parser.h"

bool ParserTest_parse() {
    std::string xml = "<?xml version='1.0' encoding='utf-8' ?>"
                      "<node_list>\n"
                      "  <node id='1'>\n"
                      "    Very important string\n"
                      "  </node>\n"
                      "other string\n"
                      "  <node id='2' property='value1' hello='world'>\n"
                      "    Text in node with id='2'"
                      "  </node>"
                      "text"
                      "</node_list>";
    Parser p((Lexer(xml)));
    Parser::XmlGraphPtr g = p.parse();
    std::cout << "1" << std::endl;
}
