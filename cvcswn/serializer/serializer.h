#pragma once

#include<string>
#include"../storage/storage.h"

class Serializer {
    public:
        static void save (Storage &storage);

        static void load (Storage &storage);
};
