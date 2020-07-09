#include "LexerTest.h"
#include "xml/Lexer.h"
#include "asserts.h"



bool LexerTest_rightXml() {
    std::string xml = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                      "<root>\n"
                      "    <el property=\'123 \"Poperty\" 75\' value = 'cinema'>\n"
                      "       value=\"123Text458\"\n"
                      "    </el>\n"
                      "</root>";
    Lexer lex(xml);
    std::vector<Token> res;
    Token tok = lex.next();
    while(tok.type != Token::END) {
        res.push_back(tok);
        tok = lex.next();
    }
    std::vector<Token> ok = {{"<?xml", Token::BEGIN_PROLOG},
                             {"version", Token::VARIABLE}, {"=", Token::EQ}, {"\"", Token::DQUOTE}, {"1.0", Token::STRING}, {"\"", Token::DQUOTE},
                             {"encoding", Token::VARIABLE}, {"=", Token::EQ}, {"\"", Token::DQUOTE}, {"utf-8", Token::STRING}, {"\"", Token::DQUOTE},
                             {"?>", Token::END_PROLOG},
                             {"<", Token::OPEN_QUOTE_BLOCK}, {"root", Token::VARIABLE}, {">", Token::CLOSE_QUOTE_BLOCK},
                             {"<", Token::OPEN_QUOTE_BLOCK},  {"el", Token::VARIABLE},
                             {"property", Token::VARIABLE}, {"=", Token::EQ}, {"\'", Token::QUOTE}, {"123 \"Poperty\" 75", Token::STRING}, {"\'", Token::QUOTE},
                             {"value", Token::VARIABLE}, {"=", Token::EQ}, {"\'", Token::QUOTE}, {"cinema", Token::STRING}, {"\'", Token::QUOTE},
                             {">", Token::CLOSE_QUOTE_BLOCK},
                             {"value=\"123Text458\"\n", Token::STRING},
                             {"</", Token::OPEN_QUOTE_END_BLOCK}, {"el", Token::VARIABLE}, {">", Token::CLOSE_QUOTE_BLOCK},
                             {"</", Token::OPEN_QUOTE_END_BLOCK}, {"root", Token::VARIABLE}, {">", Token::CLOSE_QUOTE_BLOCK}};
    return assertEq(ok, res, __FUNCTION__);
}