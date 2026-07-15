#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include"serializer.h"
#include"../storage/storage.h"

//sorry,
//but this is the most messy and unoptimized part of my code
//had a lot of trouble to learn how serialization/deserialization works

void Serializer::save (Storage &storage) {
    std::ofstream line_save;
    line_save.open("./saves/line_save.dat");

    if (line_save.fail()) {
        std::cout << "failed to create save file, changes reverted" << std::endl;
        return;
    }

    std::string text;

    for (int i = 0; i < storage.get_numberOf_lines(); i++) {
        text.append(storage[i]);
    }

    //the line_save.dat will then look like:
    //    line a
    //    line b
    //    line c
    //    ...
    //    line z
    line_save << text;

    if (line_save.fail()) {
        std::cout << "failed to save contents" << std::endl;
        line_save.close();
        return;
    }

    line_save.close();

    auto file_names = storage.get_file_names();

    //each file's saved data will then look like:
    //    name.txt
    //    0
    //    1
    //    2
    //    ...
    //    n
    for (int i = 0; i < file_names.size(); i++) {
        std::string path = "./saves/";
        path.append(file_names[i]);
        path.append(".dat");

        std::ofstream file_save;
        file_save.open(path);

        if (file_save.fail()) {
            std::cout << "failed to save file: " << file_names[i] << std::endl;
            continue;
        }

        file_save << file_names[i] << '\n';

        auto line_positions = storage.get_file_positions(file_names[i]);

        for (int i = 0; i < line_positions.size(); i++) {
            if (file_save.fail()) {
                std::cout << "save of \"" << path << "\" corrupted";
                break;
            }

            file_save << line_positions[i] << '\n';
        }

        file_save.close();
    }
}

void Serializer::load (Storage &storage) {
    for (auto &entry : std::filesystem::directory_iterator("./saves/")) {
        auto path = entry.path();

        if (!path.filename().compare("line_save.dat")) {
            std::ifstream saved_lines;
            std::string line;

            saved_lines.open(path);

            while (true) {
                std::getline(saved_lines, line);

                if (saved_lines.fail()) {
                    return;
                }

                if (saved_lines.eof()) {
                    break;
                }

                line.push_back('\n');

                storage.add_line(line);
            }

            saved_lines.close();
            continue;
        }

        std::ifstream saved_file;
        saved_file.open(path);

        std::string file_name;
        std::vector<size_t> line_positions;

        std::getline(saved_file, file_name);

        while (true) {
            std::string position;
            std::getline(saved_file, position);

            if (saved_file.eof()) {
                break;
            }

            line_positions.push_back(std::stoi(position));
        }

        storage.add_file(file_name, line_positions);
        saved_file.close();

    }

}
