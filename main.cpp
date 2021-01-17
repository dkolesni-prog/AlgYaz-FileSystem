#include <iostream>
#include <filesystem>

//1)+ вывод на экран текущего каталога (current path);
//2)+ вывод на экран содержимого каталога (только названия файлов/каталогов, без пути);
//3)+ создание каталога (папки) с предварительной проверкой на существование одноимённого
//каталога;
//4)+ вывод на экран размера файла;
//5)+ копирование файла;
//6)+ удаление файла;
//7)+ удаление каталога с файлами;
//8)+ перемещение по каталогам (вверх и вниз по вложенности);
//9)+ переименование файлов и каталогов;
//10)+ перемещение файлов и каталогов.
namespace fs = std::filesystem;
int main(int argc, char* argv[]) {
    const fs::path currentPath(argv[0]);
    const fs::path currentDir = currentPath.parent_path();
    std::cout << "Current Directory : " << currentDir << std::endl ;

    std::string path = "/Users/daniilkolesnik/Desktop/Laba";
    for (const auto & entry : fs::directory_iterator(path)) {
        std::filesystem::path tmp(entry.path());
        std::cout << tmp.filename() << std::endl;
    }

    std::cout << "Enter catalog name: " << std::endl;
    std::string dir_name;
    std::cin >> dir_name;
    bool flag = false;
    for (const auto & entry : fs::directory_iterator(path)){
        std::filesystem::path tmp(entry.path());
        if (tmp.filename() == dir_name) flag = true;
    }
    if (flag == false) fs::create_directory(path + "/" + dir_name);
    else std::cout << "Already exists" << std::endl;

    std::cout << fs::file_size(argv[0]) << std::endl;

    fs::copy_file(argv[0], path + "/my_copy");

    std::cout << "Enter file name to delete: " << std::endl;
    std::string to_delete;
    std::cin >> to_delete;
    fs::remove(path + "/" + to_delete);

    std::cout << "Enter dir name to delete: " << std::endl;
    std::cin >> to_delete;
    fs::remove_all(path + "/" + to_delete);

    fs::path work_trail  (path);
    std::cout << work_trail << std::endl;
    std::cout << work_trail.parent_path() << std::endl;
    work_trail = fs::path(path + "/DOWN");
    std::cout << work_trail << std::endl;

    std::cout << "Enter name of a file to rename" << std::endl;
    std::string file;
    std::cin >> file;
    std::cout << "Enter new name" << std::endl;
    std::string new_name;
    std::cin >> new_name;
    fs::rename(path + "/" + file , path + "/" + new_name );

    std::cout << "Enter name of a file to move" << std::endl;
    std::string to_move;
    std::cin >> to_move;
    fs::copy_file(path + "/" + to_move, path + "/DOWN/" + to_move);
    fs::remove(path + "/" + to_move);


    return 0;
}
