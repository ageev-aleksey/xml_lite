//#include "filesystem/Directory.h"
#include "entity/ParamTextSerializer.h"
#include "entity/TableSerializer.h"
#include <experimental/filesystem>
#include "xml/XmlParser.h"
#include "demon/Demon.h"
#include <iostream>
#include <fstream>
#include <thread>


namespace fs = std::experimental::filesystem;


class App : public Demon::Worker {
public:
    App(const std::string &inputFile, const std::string &outputPath, const std::string &toDeletePath,
            const std::string &numberLastFile)
    : mOutputFile(outputPath), mInputFileName(inputFile), mToDeletePath(toDeletePath),
      mFileNameFileNumber(numberLastFile) ,mLastFileNumber(0)
    {
        mParser.addSerializer<Table>(std::make_shared<TableSerializer>());
        mParser.addSerializer<ParamText>(std::make_shared<ParamTextSerializer>());
        auto pPath = mInputFileName.parent_path();
        if(!fs::exists(pPath)) {
            fs::create_directory(pPath);
        }
        pPath = mOutputFile.parent_path();
        if(!fs::exists(pPath)) {
            fs::create_directory(pPath);
        }
        if(!fs::exists(mToDeletePath)) {
            fs::create_directory(mToDeletePath);
        }
        std::fstream fl(mFileNameFileNumber, std::ios::out | std::ios::in | std::ios::app);
        if(!fl.is_open()) {
            std::stringstream msg;
            msg << "error opening file: " << numberLastFile;
            throw std::runtime_error(msg.str());
        }
        fl.clear();
        fl.seekg(0);
        fl >> mLastFileNumber;
        fl.close();
    }
    void start() override  {
        while(!isStop()) {
            std::ifstream inputFile(mInputFileName);
            if(inputFile.is_open()) {
                std::stringstream sbuff;
                sbuff << inputFile.rdbuf();
                auto table = mParser.deserialize<Table>(sbuff.str());
                inputFile.close();
                char buff[5];
                std::sprintf(buff,"%04d", ++mLastFileNumber);
                fs::path tdp = mToDeletePath;
                fs::rename(mInputFileName, tdp.append(mInputFileName.filename().string() + "." + buff));
                std::ofstream fl(mFileNameFileNumber);
                fl << mLastFileNumber;
                fl.close();
                std::ofstream outputFile(mOutputFile);
                std::stringstream fbuff;
                for(const auto &el : table.users) {
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
    }
private:
    Xml mParser;
    fs::path mOutputFile;
    fs::path mInputFileName;
    fs::path mToDeletePath;
    std::string mFileNameFileNumber;
    int mLastFileNumber;
};

#include <iostream>
#include <string>

int main() {
    App app("input_data/test.xml", "output_data/out.txt", "to_delete/", "output_data/file_last_number.txt");
    app.start();
}