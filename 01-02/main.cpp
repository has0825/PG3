#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

bool compareStudentId(const std::string& a, const std::string& b) {
    auto extractId = [](const std::string& mail) {
        return mail.substr(0, mail.find('@'));
        };

    std::string idA = extractId(a);
    std::string idB = extractId(b);

    int yearA, numA;
    int yearB, numB;
    char k, g;
    std::stringstream(idA) >> k >> yearA >> g >> numA;
    std::stringstream(idB) >> k >> yearB >> g >> numB;

    if (yearA != yearB) return yearA < yearB;
    return numA < numB;
}

int main() {
    std::ifstream file("PG3_2025_01_02.txt");

    std::string line;
    std::getline(file, line);
    file.close();

    std::vector<std::string> emails;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        if (!token.empty()) {
            emails.push_back(token);
        }
    }

    std::sort(emails.begin(), emails.end(), compareStudentId);

    for (const auto& e : emails) {
        std::cout << e << std::endl;
    }

    return 0;
}
