#include<iostream>
#include<cstring>
#include<memory>
#include"storage_manager/storage_manager.h"
#include"serializer/serializer.h"
#include"storage/storage.h"

void argument_handler (char **files, int size, char *option) {

    //using a smart pointer to handle the storage in the heap
    std::shared_ptr<Storage> storage(new Storage);
    Serializer::load(*storage);

    if (!std::strcmp(option, "ingest")) {

        Storage_manager::ingest(*storage, files, size);
        Serializer::save(*storage);
    }

    else if (!std::strcmp(option, "rebuild")) {

        Storage_manager::rebuild(*storage, files, size);
    }

    else {
        std::cout << "invalid option" << std::endl;
    }
}

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "missing args" << std::endl;
        return 1;
    }

    argument_handler(argv, argc, argv[1]);
    
    return 0;
}
