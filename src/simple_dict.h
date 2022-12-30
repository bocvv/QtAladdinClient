/*************************************************************************
	> File Name: simple_dict.h
	> Author: Bowei Wang
	> Mail: wangbw@rd.netease.com
	> Created Time: 六  12/03 17:08:05 2020
 ************************************************************************/

#ifndef _SIMPLE_DICT_H
#define _SIMPLE_DICT_H

#include <string>
#include <cstdlib>

using namespace std;

//定义词条类
class Word
{
public:
    void set(string e, string c, string wc);
    int compare(string);  //英语部分与给定字符串比较，等于返回，大于返回，小于返回-1
    string getChinese();
    string getWord_class();
private:
    string english;
    string chinese;
    string word_class;
};

//定义字典类
class Dictionary
{
public:
    Dictionary();
    void searchWord(const string &key, string &word_class, string &word_chinese);
private:
    int BinSeareh(int low, int high, const string &key);
    int wordsNum;
    Word words[8000]; //用于保存词库
};


#endif
