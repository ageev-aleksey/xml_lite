//
// Created by nrx on 11.07.2020.
//

#ifndef XML_DEMON_DAEMON_H
#define XML_DEMON_DAEMON_H
#include <memory>


class Daemon {
public:
    class Worker {
    public:
        Worker();
        virtual void start() = 0;
        virtual ~Worker() = default;
        friend class Daemon;
    protected:
        bool isStop();
    private:
        void setDaemonPtr(Daemon *ptr);
        Daemon *mPtr;
    };
    Daemon(const std::shared_ptr<Worker> &worker, const std::string &appName);
    Daemon(const Daemon&) = delete;
    ~Daemon();
    static void stop(const std::string &appName);
    void start();
    bool isStop();

private:
    std::shared_ptr<Worker> mWorker;
    std::string mAppName;

};
#endif //XML_DEMON_DAEMON_H
