#pragma once

#include<unordered_map>
#include<vector>
#include<string>

class Storage {
    private:
        std::hash<std::string> hash;

        std::vector<std::string> lines;
        std::unordered_map<size_t, size_t> line_positions;
        std::unordered_map<std::string, std::vector<size_t>> files;

    public:
        void add_file (std::string file_name);

        //to insert the files into the storage from the saved data
        void add_file (std::string file_name, std::vector<size_t> line_order);

        //to insert the lines into the storage from the saved data
        void add_line (std::string line);

        void push (std::string file_name, std::string line);

        void remove_file (std::string file_name);

        bool isStored (std::string file_name);

        std::vector<size_t> get_file_positions (std::string file_name);

        std::vector<std::string> get_file_names ();

        size_t get_numberOf_lines ();

        void debug_print ();

        //to access the vector lines more "directly"
        std::string operator[] (size_t i);
};
