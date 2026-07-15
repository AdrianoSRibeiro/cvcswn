#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include"storage.h"

void Storage::add_file (std::string file_name) {
    std::vector<size_t> line_order;
    this->files[file_name] = line_order;
}

void Storage::add_file (std::string file_name, std::vector<size_t> line_order) {
    this->files.insert({file_name, line_order});
}

void Storage::add_line (std::string line) {
    this->line_positions.insert({this->hash(line), this->lines.size()});
    this->lines.push_back(line);
}

void Storage::push (std::string file_name, std::string line) {
    line += '\n'; //adding a new line because of std::getline removing the \n
    size_t id = this->hash(line); //the key of line_positions

    if (this->line_positions.find(id) == this->line_positions.end()) {
        //the line will be added at the end of the array (arr[size])
        this->line_positions.insert({id, this->lines.size()});
        this->lines.push_back(line);
    }

        this->files[file_name].push_back(this->line_positions[id]);

}

bool Storage::isStored (std::string file_name) {
    if (this->files.find(file_name) != this->files.end()) {
        return true;
    }

    return false;
}

std::vector<size_t> Storage::get_file_positions (std::string file_name) {
    return this->files[file_name];
}

std::vector<std::string> Storage::get_file_names () {
    std::vector<std::string> file_names;

    for (auto &x : this->files) {
        file_names.push_back(x.first);
    }

    return file_names;
}

size_t Storage::get_numberOf_lines () {
    return this->lines.size();
}

std::string Storage::operator[] (size_t i) {
    return this->lines[i];
}
