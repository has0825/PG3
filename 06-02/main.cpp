#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <filesystem>

std::vector<std::vector<int>> g_mapData;
std::mutex g_mtx;
std::atomic<bool> g_isRunning(true);

// CSV読み込み
std::vector<std::vector<int>> loadMapFromCSV(const std::string& filename) {
    std::vector<std::vector<int>> newMap;
    std::ifstream file(filename);
    if (!file.is_open()) return newMap;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<int> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            try { row.push_back(std::stoi(cell)); }
            catch (...) { row.push_back(0); }
        }
        if (!row.empty()) newMap.push_back(row);
    }
    return newMap;
}

// バックグラウンド処理
void backgroundTask() {
    while (g_isRunning) {
        auto tempMap = loadMapFromCSV("map.csv");
        if (!tempMap.empty()) {
            std::lock_guard<std::mutex> lock(g_mtx);
            g_mapData = tempMap;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {

    std::cout << "\033[?25l";

    std::cout << "\033[2J";

    std::thread bgThread(backgroundTask);

    std::cout << "Map Viewer Started.\n";

    while (g_isRunning) {

        std::stringstream buffer;

        
        buffer << "\033[H";

        buffer << "=== Current Map Data ===\n";

        {
            std::lock_guard<std::mutex> lock(g_mtx);
            if (g_mapData.empty()) {
                buffer << "Loading map...\n";
            } else {
                for (const auto& row : g_mapData) {
                    for (int cell : row) {
                        if (cell == 1) {
                            buffer << "██";
                        } else {
                            buffer << "  ";
                        }
                    }
                    buffer << "\n";
                }
            }
        }

        std::cout << buffer.str();

        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    std::cout << "\033[?25h";
    bgThread.join();
    return 0;
}