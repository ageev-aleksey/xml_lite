#include "xml/Parser.h"
#include "xml/exception/XmlParseError.h"

Parser::Parser(Lexer lexer) : lexer(std::move(lexer)), graph(new XmlGraph)
{}

Parser::XmlGraphPtr Parser::parse() {
    auto ptr = new XmlNode();
    ptr->name = "~DOCUMENT~";
    auto root = graph->addNode(ptr);
    parseDocument(root);
    return std::move(graph);
}

/**
 *  document ::= prolog root
 */
void Parser::parseDocument(Graph<XmlNode *>::Iterator& node) {
    parseProlog(node);
    parseRoot(node);
}

void Parser::parseProlog(Graph<XmlNode *>::Iterator &node) {
    Token token = lexer.next();
    if(token.type == Token::BEGIN_PROLOG) {
        std::unordered_map<std::string, std::string> props;
        parsePropertyList(props);
        token = lexer.next();
        if(token.type == Token::END_PROLOG) {
            (*node)->props = std::move(props);
        } else {
            throw XmlParserError("Expected symbol '%>'; Actual symbol '" + token.str + "';");
        }
    } else {
        lexer.back();
    }

}


/**
 * root ::= node
 */
void Parser::parseRoot(Graph<XmlNode*>::Iterator& node) {
    parseNode(node);
}

/**
 * node ::= '<' VARIABLE property_list '>' body_element_list '</' STRING '>'
 */
void Parser::parseNode(Graph<XmlNode*>::Iterator& node) {
    Token token = lexer.next();
    if(token.type == Token::OPEN_QUOTE_BLOCK) {
        token = lexer.next();
        if(token.type == Token::VARIABLE) {
            std::string blockName = std::move(token.str);
            std::unordered_map<std::string, std::string> props;
            parsePropertyList(props);
            token = lexer.next();
            if(token.type == Token::CLOSE_QUOTE_BLOCK) {
                auto *block = new XmlNode;
                block->name = blockName;
                block->props = std::move(props);
                auto blockNode = graph->addNode(block);
                graph->addLink(node, blockNode);
                parseBodyElementList(blockNode);
                token = lexer.next();
                if(token.type == Token::OPEN_QUOTE_END_BLOCK) {
                    token = lexer.next();
                    if(token.type == Token::VARIABLE && token.str == blockName) {
                        token = lexer.next();
                        if(token.type == Token::CLOSE_QUOTE_BLOCK) {
                            return;
                        } else {
                            throw XmlParserError("Expected symbol '>'; Actual symbol '" + token.str + "';");
                        }
                    } else {
                        throw XmlParserError("Expected VARIABLE: '" + blockName + "'; Actual symbol '" + token.str +"';");
                    }
                } else {
                    throw XmlParserError("Expected symbol '</'; Actual symbol '" + token.str + "';");
                }
            } else {
                throw XmlParserError("Expected symbol '>'; Actual symbol '" + token.str + "';");
            }
        } else {
            throw XmlParserError("Expected symbol type VARIABLE Actual symbol: '" + token.str + "';");
        }
    } else {
        throw XmlParserError("Expected symbol '<'; Actual symbol '" + token.str + "';");
    }
}

void Parser::parsePropertyList(std::unordered_map<std::string, std::string> &props) {
    Token token = lexer.next();
    if(token.type == Token::VARIABLE) {
        std::string variable = std::move(token.str);
        token = lexer.next();
        if(token.type == Token::EQ) {
            ///token = lexer.next();
            std::string value = parseValue();
            props.emplace(std::move(variable), std::move(value));
            parsePropertyList(props);
        } else {
            throw XmlParserError("Expected symbol '='; Actual symbol '" + token.str + "';");
        }
    } else {
        lexer.back();
        return;
    }
}

std::string Parser::parseValue() {
    Token token = lexer.next();
    if(token.type == Token::QUOTE || token.type == Token::DQUOTE) {
        Token::Type qt = token.type;
        token = lexer.next();
        if(token.type == Token::STRING) {
            std::string value = std::move(token.str);
            token = lexer.next();
            if(token.type == qt) {
                return value;
            } else {
                std::stringstream msg;
                msg << "Expected symbol " << qt << " Actual symbol '" << token.str << "';";
                throw XmlParserError(msg.str());
            }
        } else {
            throw XmlParserError("Expected symbol type STRING; Actual symbol: '" + token.str + "';");
        }
    }
    throw XmlParserError("Expected symbol ''' or '\"'; Actual symbol '" + token.str + "';");
}

/*
 * body_element_list ::= e_body_element_list | epsilon
 * e_body_element_list ::= STRING | node | body_element_list
 */
void Parser::parseBodyElementList(Graph<XmlNode*>::Iterator& node) {
    Token token = lexer.next();
    if(token.type == Token::STRING) {
        XmlText *ptr = new XmlText;
        ptr->name = "~DOCUMENT_TEXT~";
        ptr->text = std::move(token.str);
        auto textNode = graph->addNode(ptr);
        graph->addLink(node, textNode);
    } else if(token.type == Token::OPEN_QUOTE_BLOCK) {
        lexer.back();
        parseNode(node);
    } else {
        lexer.back();
        return;
    }
    parseBodyElementList(node);
}


void Parser::GraphCleaner::operator()(Graph<XmlNode*> *graph) {
    if(graph == nullptr) {
        return;
    }
    for(auto & el : *graph) {
        delete el;
        el = nullptr;
    }
    delete graph;
}
