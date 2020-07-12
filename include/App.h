//
// Created by nrx on 12.07.2020.
//

#ifndef XML_DEMON_APP_H
#define XML_DEMON_APP_H
#include "daemon/Daemon.h"
#include "xml/XmlParser.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

/**
 * @brief Класс реализующий основную логику приложения
 */
class App : public Daemon::Worker {
public:
    App(const std::string &inputFile, const std::string &outputPath, const std::string &toDeletePath,
        const std::string &numberLastFile);
    void start() override;

private:
    void fileMove(const std::string &dop = "");
    Xml mParser;
    fs::path mOutputFile;
    fs::path mInputFileName;
    fs::path mToDeletePath;
    std::string mFileNameFileNumber;
    int mLastFileNumber;
};

#endif //XML_DEMON_APP_H
