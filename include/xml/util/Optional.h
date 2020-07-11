//
// Created by nrx on 11.07.2020.
//

#ifndef XML_DEMON_OPTIONAL_H
#define XML_DEMON_OPTIONAL_H

/**
 * \brief Класс для опционального возврата объектов из методов.
 * Необходимо, что бы класс имел перемещающие конструктор и конструктор по умолчанию.
 * @tparam T тип, который будет опционально возвращаться
 */
template <typename T>
class Optional {
public:
    Optional(const T &obj) : mValue(obj), mIs(true)
    {}
    Optional(T &&obj) : mValue(std::move(obj)), mIs(true)
    {}
    Optional(const T &obj, bool flag) : mValue(obj), mIs(flag)
    {}
    Optional(T &&obj, bool flag) : mValue(std::move(obj)), mIs(flag)
    {}
    Optional() : mIs(false)
    {}
    operator bool() {
        return mIs;
    }
    T* operator->() {
        return &mValue;
    }

    T&& extract() {
        return std::move(mValue);
    }


private:
    T mValue;
    bool mIs;
};
#endif //XML_DEMON_OPTIONAL_H
