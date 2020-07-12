#include "demon/Demon.h"
#include <signal.h>
#include <fstream>
#include <unistd.h>
#include <experimental/filesystem>
 namespace fs = std::experimental::filesystem::v1;

enum DemonState : sig_atomic_t {
    NOT_RUN,
    RUN,
    RECEIVED_STOP_SIGNAL
};


volatile sig_atomic_t state = DemonState::NOT_RUN;

void signalStopDemon(int signal) {
    if(signal == SIGUSR1) {
        state = DemonState::RECEIVED_STOP_SIGNAL;
    }
}
std::string getPidFilePath(const std::string &appName) {
    return std::string("/var/run/") + fs::path(appName).filename().string() + ".pid";;
}

Demon::Demon(const std::shared_ptr<Worker> &worker, const std::string &appName) : mWorker(worker), mAppName(appName)
{
    if(worker) {
        worker->setDemonPtr(this);
        std::string pidFIlePath = getPidFilePath(appName);
        std::ofstream pidFile(pidFIlePath);
        if(!pidFile.is_open()) {
            throw std::runtime_error(std::string("error opening pid file: ") + pidFIlePath);
        }
        pidFile << getpid();
        pidFile.close();
        signal(SIGUSR1, signalStopDemon);
    } else {
        throw std::runtime_error("Invalid worker ptr");
    }

}

Demon::~Demon() {
    state = DemonState::NOT_RUN;
    try{
        auto path = getPidFilePath(mAppName);
        if(fs::exists(path)) {
            fs::remove(path);
        }
    } catch(std::exception &exp)
    {}
}

void Demon::start() {
    state = DemonState::RUN;
    mWorker->start();
    state = DemonState::NOT_RUN;
}

bool Demon::isStop() {

    if(state == DemonState::RECEIVED_STOP_SIGNAL) {
        state =  DemonState::NOT_RUN;
        std::string pidFile = getPidFilePath(mAppName);
        fs::remove(pidFile);
    }
    return state == DemonState::NOT_RUN;
}

void Demon::stop(const std::string &appName) {
    std::string pidFilePath = getPidFilePath(appName);
    std::ifstream pf(pidFilePath);
    int pid = 0;
    pf >> pid;
    pf.close();
    kill(pid, SIGUSR1);
}

bool Demon::Worker::isStop() {
    return mPtr->isStop();
}

Demon::Worker::Worker()
{}

void Demon::Worker::setDemonPtr(Demon *ptr) {
    mPtr = ptr;
}
