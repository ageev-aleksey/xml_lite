#include "xml/Graph.h"
#include "asserts.h"
#include <vector>

bool GraphTest_addNode() {
    Graph<int> g;
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    std::vector<int> res;
    for(const auto &el : g) {
        res.push_back(el);
    }
    std::vector<int> ok{1, 2, 3};
    return assertEq(ok, res, __FUNCTION__);
}


bool GraphTest_CopyConstructor() {
    Graph<int> *g = new Graph<int>;
    auto n1 = g->addNode(1);
    auto n2 = g->addNode(2);
    auto n3 = g->addNode(3);
    g->addLink(n1, n2);
    g->addLink(n1, n3);
    g->addLink(n1, n1);
    g->addLink(n3, n2);
    std::vector<int> children;
    for(const auto &el : n1.getChildren()) {
        children.push_back(*el);
    }
    std::vector<int> ok{2, 3, 1};
    bool testRes = assertEq(ok, children, std::string(__FUNCTION__) + "@CheckChildrenN1");
    ok = {2};
    children = {};
    for(const auto &el : n3.getChildren()) {
        children.push_back(*el);
    }
    testRes &= assertEq(ok, children, std::string(__FUNCTION__) + "@CheckChildrenN3");

    Graph<int> g2(*g);
    delete g;

    size_t numNodes = std::distance(g2.begin(), g2.end());
    testRes &= assertEq<size_t>(3, numNodes, std::string(__FUNCTION__) + "@NumNodesCopyGraph");
    children = {};
    n1 = g2.get(0);
    for(const auto &el : n1.getChildren()) {
        children.push_back(*el);
    }
    ok = {2, 3, 1};
   testRes &= assertEq(ok, children, std::string(__FUNCTION__) + "@CheckChildrenOfCopyGraphN1");

    children = {};
    n3 = g2.get(2);
    for(const auto &el : n3.getChildren()) {
        children.push_back(*el);
    }
    ok = {2};
    testRes &= assertEq(ok, children, std::string(__FUNCTION__) + "@CheckChildrenOfCopyGraphN3");
    return testRes;
}


bool GraphTest_GetByIndex() {
    Graph<int> g;
    g.addNode(0);
    g.addNode(1);
    auto n2 = g.addNode(2);
    auto _n2 = g.get(2);
    if(_n2 == n2) {
        std::cout << "Test OK: " << __FUNCTION__ << std::endl;
        return true;
    } else {
        std::cout << "Test Fail: " << __FUNCTION__ << std::endl;
        return false;
    }
}


bool GraphTest_GetByWrongIndex1() {
    Graph<int> g;
    g.addNode(0);
    g.addNode(1);
    g.addNode(2);
    auto n3 = g.get(3);
    if(n3 == g.end()) {
        std::cout << "Test OK: " << __FUNCTION__ << std::endl;
        return true;
    } else {
        std::cout << "Test Fail: " << __FUNCTION__ << std::endl;
        return false;
    }
}

bool GraphTest_GetByWrongIndex2() {
    Graph<int> g;
    g.addNode(0);
    g.addNode(1);
    g.addNode(2);
    auto n5 = g.get(5);
    if(n5 == g.end()) {
        std::cout << "Test OK: " << __FUNCTION__ << std::endl;
        return true;
    } else {
        std::cout << "Test Fail: " << __FUNCTION__ << std::endl;
        return false;
    }
}