#include "assets_manager.h"

#include <iostream>

#include <zip.h>
#include <SQLiteCpp/SQLiteCpp.h>

void* LoadAsset(const char* path, size_t *size_data) {
    // Connect to database
    SQLite::Database db("assets_db.sqlite", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // Get zip file path
    SQLite::Statement query(db, std::string("SELECT WherePath FROM assets WHERE Name = '") + path + "'");
    query.executeStep();

    std::string zip_path = query.getColumn(0).getString();
    std::cout << "Zip path: " << zip_path << std::endl;

    // Open zip file
    zip_t* zip = zip_open(zip_path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
    if (!zip) {
        std::cout << "Failed to open zip file" << std::endl;
        return nullptr;
    }

    unsigned char* buf = nullptr;

    zip_entry_open(zip, path);
        size_t s = zip_entry_size(zip);
        buf = (unsigned char*)calloc(sizeof(unsigned char), s);

        zip_entry_noallocread(zip, (void *)buf, s);
    zip_entry_close(zip);

    *size_data = s;

    zip_close(zip);

    return (void*)buf;
}
