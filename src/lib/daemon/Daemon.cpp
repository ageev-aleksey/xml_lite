#include "daemon/Daemon.h"
#include <csignal>
#include <fstream>
#include <unistd.h>
#include <experimental/filesystem>
 namespace fs = std::experimental::filesystem::v1;

enum DaemonState : sig_atomic_t {
    NOT_RUN,
    RUN,
    RECEIVED_STOP_SIGNAL
};


volatile sig_atomic_t state = DaemonState::NOT_RUN;

void signalStopDemon(int signal) {
    if(signal == SIGUSR1) {
        state = DaemonState::RECEIVED_STOP_SIGNAL;
    }
}
std::string getPidFilePath(const std::string &appName) {
    return std::string("/var/run/") + fs::path(appName).filename().string() + ".pid";;
}

Daemon::Daemon(const std::shared_ptr<Worker> &worker, const std::string &appName) : mWorker(worker), mAppName(appName)
{
    if(worker) {
        worker->setDaemonPtr(this);
        std::string pidFIlePath = getPidFilePath(appName);
        std::ofstream pidFile(pidFIlePath);
        if(!pidFile.is_open()) {
            throw std::runtime_error(std::string("error opening pid file: ") + pidFIlePath);
        }
        pidFile << getpid();
        pidFile.close();
        if(signal(SIGUSR1, signalStopDemon) == SIG_ERR) {
            throw std::runtime_error("Error registration signal handler (" +  std::to_string(errno) + ")");
        }
    } else {
        throw std::runtime_error("Invalid worker ptr");
    }

}

Daemon::~Daemon() {
    state = DaemonState::NOT_RUN;
    try{
        auto path = getPidFilePath(mAppName);
        if(fs::exists(path)) {
            fs::remove(path);
        }
    } catch(std::exception &exp)
    {}
}

void Daemon::start() {
    state = DaemonState::RUN;
    mWorker->start();
    state = DaemonState::NOT_RUN;
}

bool Daemon::isStop() {

    if(state == DaemonState::RECEIVED_STOP_SIGNAL) {
        state =  DaemonState::NOT_RUN;
        std::string pidFile = getPidFilePath(mAppName);
        fs::remove(pidFile);
    }
    return state == DaemonState::NOT_RUN;
}

void Daemon::stop(const std::string &appName) {
    std::string pidFilePath = getPidFilePath(appName);
    std::ifstream pf(pidFilePath);
    if(!pf.is_open()) {
        throw std::runtime_error("Not opened pid file: " + pidFilePath);
    }
    int pid = 0;
    pf >> pid;
    pf.close();
    if(kill(pid, SIGUSR1) == -1) {
        std::stringstream msg;
        msg << "Error sending signal SIGUSR1 to processor with pid " << pid << " (" << errno << ")";
        throw std::runtime_error(msg.str());
    }
}

bool Daemon::Worker::isStop() {
    return mPtr->isStop();
}

Daemon::Worker::Worker()
{}

void Daemon::Worker::setDaemonPtr(Daemon *ptr) {
    mPtr = ptr;
}
