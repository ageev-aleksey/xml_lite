#include "demon/Demon.h"


class DemonImpl {
public:
    DemonImpl(const std::shared_ptr<Demon::Worker> &worker) : mWorker(worker)
    {}
    void start() {

    }
private:
    std::shared_ptr<Demon::Worker> mWorker;
};

Demon::Demon(const std::shared_ptr<Worker> &worker) : pimpl(new DemonImpl(worker))
{}

Demon::~Demon() {
    delete pimpl;
}

void Demon::start() {
    pimpl->start();
}

bool Demon::Worker::isStop() {
    return mIsStop;
}

Demon::Worker::Worker() : mIsStop(false)
{}
