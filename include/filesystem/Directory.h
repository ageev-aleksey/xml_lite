//
// Created by nrx on 11.07.2020.
//

#ifndef XML_DEMON_DIRECTORY_H
#define XML_DEMON_DIRECTORY_H
#include <string>
#include <list>

class DirectoryImpl;

/**
 * \brief Класс описывающий директорию
 */
class Directory {
public:
    /**
     * \brief Конструктор создающий объект, директорию необходимо открыть методом \see open
     */
    Directory();
    Directory(const Directory &dir);
    ~Directory();

    /**
     *  Открытие директори по указанному пути
     * @param path путь до дериктории
     * @return
     */
    bool open(std::string path = ".");
    /**
     * \brief список файлов в открытой директории
     * @return список файлов
     */
    std::list<std::string> files();

private:
    DirectoryImpl *pimpl;
};


#endif //XML_DEMON_DIRECTORY_H
