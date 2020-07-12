//
// Created by nrx on 11.07.2020.
//

#ifndef XML_DEMON_DEMON_H
#define XML_DEMON_DEMON_H
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
        void setDemonPtr(Demon *ptr);
        Demon *mPtr;
    };
    Demon(const std::shared_ptr<Worker> &worker, const std::string &appName);
    Demon(const Demon&) = delete;
    ~Demon();
    static void stop(const std::string &appName);
    void start();
    bool isStop();

private:
    std::shared_ptr<Worker> mWorker;
    std::string mAppName;

};
#endif //XML_DEMON_DEMON_H
