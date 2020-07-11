//
// Created by nrx on 11.07.2020.
//

#ifndef XML_DEMON_DIRECTORY_H
#define XML_DEMON_DIRECTORY_H
#include <string>
#include <vector>

class DirectoryImpl;

/**
 * \brief Класс описывающий директорию
 */
class Directory {
public:
    /**
     * \brief Конструктор создающий объект, директорию необходимо открыть методом \see open
     */
    explicit Directory(const std::string &path= ".");
    Directory(const Directory &dir);
    ~Directory();

    /**
     *  Открытие директори по указанному пути
     * @param path путь до дериктории
     * @return
     */
    bool open();
    /**
     * \brief список файлов в открытой директории
     * @return список файлов
     */
    std::vector<std::string> files();
    /**
     * \brief Метод проверяет, существует ли директория.
     * @return Существует ли дериктория
     */
    bool isExists();

private:
    DirectoryImpl *pimpl;
};


#endif //XML_DEMON_DIRECTORY_H
