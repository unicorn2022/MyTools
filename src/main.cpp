#pragma warning(disable : 4996)
#include "../include/EPUB_TO_TXT.h"
#include "../include/TXT_TO_TXT.h"
#include "../include/TXT_TO_TXT_Delete_Space.h"
#include "../include/LRC_TO_ASS.h"
#include "../include/SRT_TO_ASS.h"


#include <io.h>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
using namespace std;

/*
path: 指定目录
files: 保存结果
fileType: 指定的文件格式，如 .jpg
*/
void getAllFiles(string path, vector<string>& files, string fileType);

bool Work();

int main() {
    while (Work());
    return 0;
}

bool Work() {
    string source;
    string fileType = "wav";
    string targetType = "ass";

    /* 输入信息 */
    {
        printf("请输入源文件路径, 输入~终止程序:\033[33m");
        cin >> source;
        printf("\033[0m");

        if (source.compare("~") == 0) return false;

        printf("请输入源文件类型:\033[33m");
        cin >> fileType;
        printf("\033[0m");

        printf("请输入目标文件类型:\033[33m");
        cin >> targetType;
        printf("\033[0m");
    }

    
    
    if (source.size() == 0) {
        // EPUB_TO_TXT::Main();
        // TXT_TO_TXT::Main();
        // TXT_TO_TXT_Delete_Space::Main();
        // LRC_TO_ASS::Main();
        SRT_TO_ASS::Main();
    }
    else {
        vector<string> files;
        getAllFiles(source, files, fileType);

        // 对每一个file, 执行一次程序
        int cnt = 0;
        for (auto file : files) {
            /* 重命名文件 */
            {
                cnt++;
                string command = "rename " + file + " Kokomi_" + to_string(cnt) + ".mp3";
                system(command.c_str());
            }

            /* 文件格式转换 */
            {
                size_t pos = file.find_last_of(".");
                string name = file.substr(0, pos);
                string target = name + "." + targetType;

                // EPUB_TO_TXT::Main();
                // TXT_TO_TXT::Main();
                // TXT_TO_TXT_Delete_Space::Main();
                // LRC_TO_ASS::Main(file.c_str(), target.c_str());
                // SRT_TO_ASS::Main(file.c_str(), target.c_str());
            }
        }
    }
    return true;
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

    printf("path: %s, files count = %d\n", path.c_str(), files.size());
}