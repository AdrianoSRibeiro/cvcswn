#include<iostream>
#include<cstring>
#include<fstream>
#include"../storage/storage.h"
#include"storage_manager.h"

void Storage_manager::ingest (Storage &storage, char **file_names, int size) {
    std::ifstream file;
    std::string path;
    path.reserve(64);

    for (int i = 2; i < size; i++) {

        if (storage.isStored(file_names[i])) {
            //this function shouldn't have the responsibility print errors,
            //but organizing an error structure to do it in main would be
            //time consuming
            std::cout << "file already saved: " << file_names[i] << std::endl;
            continue;
        }

        //I didn't want to have every file in the program's input be thrown around
        //in the project folder, so I made the input directory so the files are
        //stored in there
        path = "./input/";
        path += file_names[i];
        file.open(path);

        if (file.fail()) {
            std::cout << "error on opening file: " << file_names[i] << std::endl;
            continue;
        }

        storage.add_file(file_names[i]);

        while (true) {
            std::string line;
            std::getline(file, line);

            if (file.eof()) {
                break;
            }

            storage.push(file_names[i], line);
        }

        std::cout << "saved file: " << file_names[i] << std::endl;

        file.close();
    }
}

void Storage_manager::rebuild (Storage &storage, char **file_names, int size) {
    std::ofstream file;
    std::string path;
    path.reserve(64);

    for (int i = 2; i < size; i++) {

        if (!storage.isStored(file_names[i])) {
            std::cout << "file isn't saved: " << file_names[i] << std::endl;
            continue;
        }

        path = "./output/";
        path += file_names[i];
        file.open(path);

        if (file.fail()) {
            std::cout << "error on creating file: " << file_names[i] << std::endl;
            continue;
        }

        std::string text;
        std::vector<size_t> line_positions = storage.get_file_positions(file_names[i]);

        for (size_t line : line_positions) {
            text += storage[line];
        }

        file << text;

        if (file.fail()) {
            std::cout << "error on writing file: " << file_names[i] << std::endl;
        }
        else {
            std::cout << "rebuilt file: " << file_names[i] << std::endl;
        }

        file.close();
    }
}
