#include <zip.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Map of all assets
std::map<std::string, std::string> assets;

void DBCreate() {
    SQLite::Database db("assets_db.sqlite", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // Table: assets
    // ID (autoincrement)
    // Name
    // WherePath (path to zip file)

    SQLite::Statement query(db, "CREATE TABLE IF NOT EXISTS assets ("
                                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "Name varchar(255), "
                                 "WherePath varchar(255));");
    query.exec();
}

void MakeZips() {
    // Remove all .zip files in ./assets/
    for (auto& p : fs::directory_iterator("./assets/")) {
        if (p.path().extension() == ".zip") {
            fs::remove(p.path());
        }
    }

    // All files in ./assets
    for (const auto& entry : fs::directory_iterator("./assets")) {
        std::string name = entry.path().filename().string();

        // Split name by _
        std::vector<std::string> split = {};
            std::stringstream ss(name);
            std::string item;
            while (std::getline(ss, item, '_')) {
                split.push_back(item);
            }

        // Open zip file split[0].zip
        zip_t* zip;
        // Create zip file if it doesn't exist, otherwise open it
        if (!fs::exists("./assets/" + split[0] + ".zip")) {
            zip = zip_open(("./assets/" + split[0] + ".zip").c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
        } else {
            zip = zip_open(("./assets/" + split[0] + ".zip").c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'a');
        }

        // Add to assets map
        assets[name] = "./assets/" + split[0] + ".zip";

        // Add to zip
        zip_entry_open(zip, name.c_str());
            // Read file
            std::ifstream file(entry.path().string(), std::ios::binary);
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string content = buffer.str();
            zip_entry_write(zip, content.c_str(), content.size());
        zip_entry_close(zip);

        zip_close(zip);
    }
}

void PopulateDB() {
    SQLite::Database db("assets_db.sqlite", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // Insert all assets into DB
    for (const auto& asset : assets) {
        SQLite::Statement query(db, "INSERT INTO assets (Name, WherePath) VALUES (?, ?);");
        query.bind(1, asset.first);
        query.bind(2, asset.second);
        query.exec();
    }
}

int main() {
    // Remove file assets_db.sqlite
    std::cout << "Removing assets_db.sqlite" << std::endl;
    if (remove("./assets_db.sqlite") != 0) {
        std::cout << "Error deleting file" << std::endl;
    }

    DBCreate();
    
    MakeZips();

    PopulateDB();

    return 0;
}