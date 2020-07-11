//
// Created by nrx on 11.07.2020.
//

#ifndef XML_DEMON_DEMON_H
#define XML_DEMON_DEMON_H
#include "demon/DemonWorker.h"
#include <memory>

class DemonImpl;

class Demon {
public:
    class Worker {
    public:
        Worker();
        virtual void start() = 0;
        virtual ~Worker() = default;
        friend class Demon;
    protected:
        bool isStop();
    private:
        bool mIsStop;
    };
    explicit Demon(const std::shared_ptr<Worker> &worker);
    ~Demon();
    void start();
    Demon(const Demon&) = delete;
private:
    DemonImpl *pimpl;

};
#endif //XML_DEMON_DEMON_H
