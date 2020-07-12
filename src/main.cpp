#include "App.h"
#include "AppException.h"

constexpr int ERROR_EXIT = -1;
constexpr int EXIT = 0;


int main(int argc, char **argv) {
    const std::string pathInputFile("input_data/test.xml");
    const std::string pathOutputFile("output_data/out.txt");
    const std::string pathToDelete("to_delete/");
    const std::string pathLastNumberFile("output_data/file_last_number.txt");
    try {
        if (argc > 1) {
            if (strncmp(argv[1], "stop", 5) == 0) {
                Daemon::stop(argv[0]);
                return EXIT;
            }
            std::cerr << "error argument" << std::endl;
            return ERROR_EXIT;
        } else {
            auto app = std::make_shared<App>(pathInputFile, pathOutputFile, pathToDelete, pathLastNumberFile);
            Daemon d(app, argv[0]);
            std::cout << "INIT" << std::endl;

            d.start();


        }
    } catch (AppException &exp) {
        std::cerr << "Application error" << std::endl;
        return ERROR_EXIT;
    } catch (std::exception &exp) {
        std::cerr << "Init application error: " << exp.what() << std::endl;
        return ERROR_EXIT;
    }

    return EXIT;
}