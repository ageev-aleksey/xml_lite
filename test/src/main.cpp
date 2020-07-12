#include <iostream>

constexpr int OK = 0;
constexpr int ERROR = -1;

bool LexerTest_rightXml();
bool GraphTest_addNode();
bool GraphTest_CopyConstructor();
bool GraphTest_GetByIndex();
bool GraphTest_GetByWrongIndex1();
bool GraphTest_GetByWrongIndex2();
//bool ParserTest_parse();
bool SerializerTest_serializeFromBody();
bool SerializerTest_serializeFromProperty();
bool SerializerTest_InvalidXmlFormat1();
bool SerializerTest_InvalidXmlFormat2();
bool SerializerTest_InvalidXmlFormat3();

int runTest() {
    bool ok = true;
    ok &= LexerTest_rightXml();
    ok &= GraphTest_addNode();
    ok &= GraphTest_CopyConstructor();
    ok &= GraphTest_GetByIndex();
    ok &= GraphTest_GetByWrongIndex1();
    ok &= GraphTest_GetByWrongIndex2();
    ok &= SerializerTest_serializeFromBody();
    ok &= SerializerTest_serializeFromProperty();
    ok &= SerializerTest_InvalidXmlFormat1();
    ok &= SerializerTest_InvalidXmlFormat2();
    ok &= SerializerTest_InvalidXmlFormat3();
    if(!ok) {
        std::cout << "Testing fail!" << std::endl;
        return ERROR;
    }
    return OK;
}


int main() {
    return  runTest();
}