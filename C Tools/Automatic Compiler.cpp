#include <iostream>   // std::cin, std::cout, std::endl, std::getline
#include <cstdio>     // freopen
#include <vector>     // std::vector
#include <set>        // std::set
#include <cstdlib>    // system (全局)
#include <string>     // std::string

bool isInclude(const std::string& str) {
    return str.find("#include") != std::string::npos;
}

std::set<std::string> included;

void printFile(const char* fileName) {
    std::string codeInput;
    freopen(fileName, "r", stdin);
    std::cin.clear();
    // 读入文件
    std::vector<std::string> file;
    while (codeInput != "END" && !std::cin.eof()) {
        std::getline(std::cin, codeInput);
        file.push_back(codeInput);
    }
    // 输出文件
    for (size_t i = 0; i < file.size(); ++i) {
        codeInput = file[i];
        if (!isInclude(codeInput)) {
            std::cout << codeInput << std::endl;
        } else {
            std::string name;
            int idx = 0;
            while (codeInput[idx] != '\"') ++idx;
            ++idx;
            while (codeInput[idx] != '\"') {
                name.push_back(codeInput[idx]);
                ++idx;
            }
            if (included.find(name) == included.end()) {
                printFile(name.c_str());
                included.insert(name);
            }
        }
    }
}

int main() {
    freopen("unfoldedcode.c", "w", stdout);
    included.insert("head.h");
    printFile("source.c");
    // system 是全局函数，不需要 std:: 前缀
    system("代码转换器.exe < unfoldedcode.c > transformedcode.c");
    system("C语言编译器.exe < transformedcode.c > fsccode.txt");
    return 0;
}
