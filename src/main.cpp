#pragma warning(disable : 4996)
#include "../include/EPUB_TO_TXT.h"
#include "../include/TXT_TO_TXT.h"
#include "../include/TXT_TO_TXT_Delete_Space.h"
#include "../include/LRC_TO_ASS.h"

#include <io.h>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/*
path: 指定目录
files: 保存结果
fileType: 指定的文件格式，如 .jpg
*/
void getAllFiles(string path, vector<string>& files, string fileType);

int main() {
    char source[500];

    printf("请输入源文件路径:\033[33m");
    cin.getline(source, 500);
    printf("\033[0m");


    if (strlen(source) == 0) {
        // EPUB_TO_TXT::Main();
        // TXT_TO_TXT::Main();
        // TXT_TO_TXT_Delete_Space::Main();
        LRC_TO_ASS::Main();

    } else {
        vector<string> files;
        const string fileType = "lrc";
        const string targetType = "ass";
        getAllFiles(source, files, fileType);

        // 对每一个file, 执行一次程序
        for (auto file : files) {
            size_t pos = file.find(".");
            string name = file.substr(0, pos);
            string target = name + "." + targetType;

            // EPUB_TO_TXT::Main();
            // TXT_TO_TXT::Main();
            // TXT_TO_TXT_Delete_Space::Main();
            LRC_TO_ASS::Main(file.c_str(), target.c_str());
        }
    }

    return 0;
}

void getAllFiles(string path, vector<string>& files, string fileType) {
    // 文件句柄
    long long hFile = 0;
    // 文件信息
    struct _finddata_t fileinfo;

    string p;

    if ((hFile = _findfirst(p.assign(path).append("\\*" + fileType).c_str(), &fileinfo)) != -1) {
        do {
            // 保存文件的全路径
            files.push_back(p.assign(path).append("\\").append(fileinfo.name));

        } while (_findnext(hFile, &fileinfo) == 0);  // 寻找下一个，成功返回0，否则-1

        _findclose(hFile);
    }
}