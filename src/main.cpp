#include <iostream>
#include <xml/Xml.h>
#include <xml/XmlObject.h>
#include <xml/XmlDeserializeContext.h>

struct User{
    std::string fname;
    std::string lname;
};


class UserSerializer : public XmlSerializer<User> {
    std::string serialize(User user) override {
        return "";
    }

    User deserialize(std::unique_ptr<XmlDeserializeContext> context) override {
        std::optional<XmlObject> userObject = context->get("user");
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
        std::optional<XmlObject> usersList = context->get("users");
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


int main() {
    Xml parser;
    parser.addSerializer<User>(std::make_shared<UserSerializer>());
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
    std::cout << "hellp";
}