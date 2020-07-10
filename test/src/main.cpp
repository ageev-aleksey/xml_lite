bool LexerTest_rightXml();
bool GraphTest_addNode();
bool GraphTest_CopyConstructor();
bool GraphTest_GetByIndex();
bool GraphTest_GetByWrongIndex1();
bool GraphTest_GetByWrongIndex2();


void runTest() {
    bool ok = true;
    ok &= LexerTest_rightXml();
    ok &= GraphTest_addNode();
    ok &= GraphTest_CopyConstructor();
    ok &= GraphTest_GetByIndex();
    ok &= GraphTest_GetByWrongIndex1();
    ok &= GraphTest_GetByWrongIndex2();

}


int main() {
    runTest();
    return 0;
}