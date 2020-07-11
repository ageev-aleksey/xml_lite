#include "xml/XmlParser.h"
#include "asserts.h"

//bool ParserTest_parse() {
//    std::string xml = "<?xml version='1.0' encoding='utf-8' ?>"
//                      "<node_list>\n"
//                      "  <node id='1'>\n"
//                      "    Very important string\n"
//                      "  </node>\n"
//                      "other string\n"
//                      "  <node id='2' property='value1' hello='world'>\n"
//                      "    Text in node with id='2'"
//                      "  </node>"
//                      "text"
//                      "</node_list>";
//    Parser p((Lexer(xml)));
//    Parser::XmlGraphPtr g = p.parse();
//    std::cout << "1" << std::endl;
//}

struct User {
    std::string fname;
    std::string lname;
};


class UserSerializer1 : public XmlSerializer<User> {
    std::string serialize(User user) override {
        return "";
    }

    User deserialize(std::unique_ptr<XmlDeserializeContext> context) override {
        Optional<XmlObject> userObject = context->get("user");
        User user;
        if(userObject) {
            user.fname = *userObject->get("fname")->getText().begin();
            user.lname = *userObject->get("lname")->getText().begin();
        }
        return user;
    }
};

class UserListSerializer : public XmlSerializer<std::list<User>> {
public:
    std::string serialize(std::list<User> user) override {
        return "";
    }

    std::list<User> deserialize(std::unique_ptr<XmlDeserializeContext> context) override {
        Optional<XmlObject> usersList = context->get("users");
        std::list<User> res;
        if (usersList) {
            std::list<XmlObject> users = usersList->asList("user");
            for (auto &el : users) {
                User user = context->deserialize<User>(el);
                res.push_back(user);
            }
        }
        return res;
    }
};


bool SerializerTest_serializeFromBody() {
    Xml parser;
    parser.addSerializer<User>(std::make_shared<UserSerializer1>());
    parser.addSerializer<std::list<User>>(std::make_shared<UserListSerializer>());
    std::string xmlStr = "<users>"
                         "  <user>"
                         "      <fname> Ivan </fname>"
                         "      <lname> Ivanov </lname>"
                         "  </user>"
                         "  <user>"
                         "      <fname> Petr </fname>"
                         "      <lname> Petrov </lname>"
                         "  </user>"
                         "</users>";
    auto res = parser.deserialize<std::list<User>>(xmlStr);

    bool ok = assertEq<size_t>(2, res.size(), __FUNCTION__);
    auto ptr = res.begin();
    ok &= assertEq<std::string>("Ivan", ptr->fname, __FUNCTION__);
    ok &= assertEq<std::string>("Ivanov", ptr->lname, __FUNCTION__);
    ++ptr;
    ok &= assertEq<std::string>("Petr", ptr->fname, __FUNCTION__);
    ok &= assertEq<std::string>("Petrov", ptr->lname, __FUNCTION__);
    return ok;
}


class UserSerializer2 : public XmlSerializer<User> {
    std::string serialize(User user) override {
        return "";
    }

    User deserialize(std::unique_ptr<XmlDeserializeContext> context) override {
        Optional<XmlObject> userObject = context->get("user");
        User user;
        if(userObject) {
            auto fname = userObject->property("fname");
            if(fname) {
                user.fname = fname.extract();
            }
            auto lname = userObject->property("lname");
            if(lname) {
                user.lname = lname.extract();
            }
        }
        return user;
    }
};


bool SerializerTest_serializeFromProperty() {
    Xml parser;
    parser.addSerializer<User>(std::make_shared<UserSerializer2>());
    parser.addSerializer<std::list<User>>(std::make_shared<UserListSerializer>());
    std::string xmlStr = "<users>"
                         "  <user fname='Ivan' lname='Ivanov'></user>"
                         "  <user fname='Petr' lname='Petrov'></user>"
                         "</users>";
    auto res = parser.deserialize<std::list<User>>(xmlStr);

    bool ok = assertEq<size_t>(2, res.size(), std::string(__FUNCTION__) + "@SizeCheck" );
    auto ptr = res.begin();
    ok &= assertEq<std::string>("Ivan", ptr->fname, std::string(__FUNCTION__) + "@FNameCheck1" );
    ok &= assertEq<std::string>("Ivanov", ptr->lname, std::string(__FUNCTION__) + "@LNameCheck1" );
    ++ptr;
    ok &= assertEq<std::string>("Petr", ptr->fname, std::string(__FUNCTION__) + "@FNameCheck2");
    ok &= assertEq<std::string>("Petrov", ptr->lname, std::string(__FUNCTION__) + "@LNameCheck2");
    return ok;
}