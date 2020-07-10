#include <memory>
#include <unordered_map>
#include <iostream>
#include <xml/Graph.h>
#include "xml/Parser.h"

class BaseXmlSerializer {
public:
    virtual ~BaseXmlSerializer() = default;
};


template <typename T> class XmlSerializer;

class Xml {
public:

    static std::unique_ptr<Xml> createInstance() {
        return std::unique_ptr<Xml>(new Xml());
    }


    template<typename T>
    void addSerializer(std::shared_ptr<XmlSerializer<T>> serializer) {
        serializers.insert({typeid(T).hash_code(), serializer});
    }
    template<typename T>
    std::shared_ptr<XmlSerializer<T>> getSerializer() {
        size_t hash = typeid(T).hash_code();
        auto ptr = serializers.find(hash);
        if(ptr != serializers.end()) {
            return std::static_pointer_cast<XmlSerializer<T>>(ptr->second);
        }
        return nullptr;
    }

    template<typename T>
    std::shared_ptr<T> deserialize(const std::string& str) {
        std::shared_ptr<XmlSerializer<T>> serializer = getSerializer<T>();
        if(serializer) {
            serializer->deserialize(str, std::unique_ptr<Context>(new Context(this)));
        }
        return nullptr;
    }


    class Context {
    public:

        template<typename T>
        std::shared_ptr<T> deserialize(std::string str) {
            std::shared_ptr<XmlSerializer<T>> ptr =  container->getSerializer<T>();
            return nullptr;
        }
        friend class Xml;
    private:
        explicit Context(Xml * xml) : container(xml) {}
        Xml *container;
    };



protected:
    Xml() = default;
private:
    std::unordered_map<size_t, std::shared_ptr<BaseXmlSerializer>> serializers;
};

template <typename T>
class XmlSerializer : public BaseXmlSerializer {
public:
    virtual std::string serialize(T object) = 0;
    virtual T deserialize(std::string, std::unique_ptr<Xml::Context> context) = 0;
    ~XmlSerializer() override = default;
};





class TestXml : public XmlSerializer<int> {
public:
    int j;
    TestXml (int i) {
        j = i;
    }
    std::string serialize(int object) override {
        return "";
    }
    int deserialize(std::string str, std::unique_ptr<Xml::Context> context)override{
        return 0;
    }

};
struct Node {
    int a;
    int b;
};

int main() {
//    std::unique_ptr<Xml> s = Xml::createInstance();
//    s->addSerializer<int>(std::make_shared<TestXml>(10));
//    auto res = s->deserialize<int>(std::string("154"));
//    std::shared_ptr<XmlSerializer<double>> int_ptr = s->getSerializer<double>();
//    std::shared_ptr<TestXml> test = std::dynamic_pointer_cast<TestXml>(int_ptr);
//    if(test) {
//        std::cout << test->j;
//    }
//    std::cout << "a";

    Graph<Node> g;
    auto i = g.addNode({1, 2});
    auto j = g.addNode({5, 10});
    g.addLink(i, j);
    auto ch = i.getChildren();
    std::cout << ch.size() << std::endl;
    for(auto el : ch) {
        std::cout << el->a << std::endl;
    }
    return 0;
}
