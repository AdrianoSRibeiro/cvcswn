#pragma once

#include"../storage/storage.h"

class Storage_manager {
    public:
        static void ingest (Storage &storage, char **file_names, int size);

        static void rebuild (Storage &storage, char **file_names, int size);

        static void remove (Storage &storage, char **file_names, int size);
};
