#include "App.h"
#include "AppException.h"
#include "entity/ParamTextSerializer.h"
#include "entity/TableSerializer.h"
#include <fstream>
#include <thread>

App::App(const std::string &inputFile, const std::string &outputPath, const std::string &toDeletePath,
         const std::string &numberLastFile)
        : mOutputFile(outputPath), mInputFileName(inputFile), mToDeletePath(toDeletePath),
          mFileNameFileNumber(numberLastFile), mLastFileNumber(0) {
    mParser.addSerializer<Table>(std::make_shared<TableSerializer>());
    mParser.addSerializer<ParamText>(std::make_shared<ParamTextSerializer>());
    auto pPath = mInputFileName.parent_path();
    if (!fs::exists(pPath)) {
        fs::create_directory(pPath);
    }
    pPath = mOutputFile.parent_path();
    if (!fs::exists(pPath)) {
        fs::create_directory(pPath);
    }
    if (!fs::exists(mToDeletePath)) {
        fs::create_directory(mToDeletePath);
    }
    std::fstream fl(mFileNameFileNumber, std::ios::out | std::ios::in | std::ios::app);
    if (!fl.is_open()) {
        std::stringstream msg;
        msg << "error opening file: " << numberLastFile;
        throw std::runtime_error(msg.str());
    }
    fl.clear();
    fl.seekg(0);
    fl >> mLastFileNumber;
    fl.close();
}


void App::start() {
    try {
        while (!isStop()) {
            std::ifstream inputFile;
            inputFile.open(mInputFileName);
            if (inputFile.is_open()) {
                std::stringstream sbuff;
                sbuff << inputFile.rdbuf();

                Table table;
                try {
                    table = mParser.deserialize<Table>(sbuff.str());
                } catch (XmlParserError &exp) {
                    std::cout << "Xml parsing error: " << exp.what() << std::endl;
                    inputFile.close();
                    fileMove("ERROR");
                    continue;
                }


                inputFile.close();
                fileMove();
                std::ofstream fl(mFileNameFileNumber);
                fl << mLastFileNumber;
                fl.close();
                std::ofstream outputFile(mOutputFile);
                std::stringstream fbuff;
                for (const auto &el : table.users) {
                    fbuff << el.name << "\n"
                          << el.date << "\n"
                          << el.hoursWorked << "\n"
                          << (el.carTrue ? "YES" : "NO") << "\n\n";
                }
                outputFile << fbuff.str();
                outputFile.close();
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    } catch (std::exception &exp) {
        std::cerr << "Unexpected error: " << exp.what() << std::endl;
        throw AppException(exp.what());
    }
}


void App::fileMove(const std::string &dop) {
    try {
        char buff[5];
        std::sprintf(buff, "%04d", ++mLastFileNumber);
        fs::path tdp = mToDeletePath;
        fs::rename(mInputFileName, tdp.append(mInputFileName.filename().string() + "." + dop + "." + buff));
    } catch (fs::filesystem_error &exp) {
        std::cerr << "Move file error (" << exp.path1().c_str() << " -> " << exp.path2() << "): " << exp.what();
        throw exp;
    }
}