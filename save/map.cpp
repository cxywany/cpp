#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
    // 创建一个 unordered_map，键为字符串，值为整数
    unordered_map<string, int> umap;

    // 插入元素
    umap["apple"] = 1;
    umap["banana"] = 2;
    umap["orange"] = 3;

    // 访问元素
    cout << "apple: " << umap["apple"] << endl; // 输出: apple: 1

    // 检查键是否存在
    if (umap.find("banana") != umap.end())
    {
        cout << "banana exists with value: " << umap["banana"] << endl; // 输出: banana exists with value: 2
    }

    // 遍历 unordered_map
    for (const auto &pair : umap)
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 删除元素
    umap.erase("orange");

    // 检查删除后的结果
    if (umap.find("orange") == umap.end())
    {
        cout << "orange has been removed." << endl; // 输出: orange has been removed.
    }

    return 0;
}
