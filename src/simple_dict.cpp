#include <fstream>
#include <iostream>
#include "simple_dict.h"

using namespace std;


void Word::set(string e, string c, string wc) {
    english=e;
    chinese=c;
    word_class=wc;
}

int Word::compare(string k) {
    return english.compare(k);
}

string Word::getChinese() {
    return chinese;
}

string Word::getWord_class() {
    return word_class;
}

Dictionary::Dictionary() {
    string e,c,wc;
    wordsNum=0;
    //将文件中的数据读入到对象数组中
    ifstream infile("Databases/dictionary.txt", ios::in);  //以输入的方式打开文件
    if(!infile)       //测试是否成功打开
    {
        cerr<<"dictionary open error!"<<endl;
        exit(1);
    }
    while (!infile.eof())
    {
        infile>>e>>c>>wc;
        words[wordsNum].set(e, c, wc);
        ++wordsNum;
    }
    infile.close();
}

int Dictionary::BinSeareh(int low, int high, const string &key) {
    int mid;
    while(low<=high)
    {
        mid=(low + high) / 2;
        if(words[mid].compare(key)==0)
        {
            return mid; //查找成功返回
        }
        if(words[mid].compare(key)>0)
            high=mid-1; //继续在w[low..mid-1]中查找
        else
            low=mid+1; //继续在w[mid+1..high]中查找
    }
    return -1; //当low>high时表示查找区间为空，查找失败
}

void Dictionary::searchWord(const string &key, string &word_class, string &word_chinese) {
    int low = 0, high = wordsNum - 1;  //置当前查找区间上、下界的初值
    int index = BinSeareh(low, high, key);

    if (index >= 0) {
        word_class = words[index].getWord_class();
        word_chinese = words[index].getChinese();
    } else {
        word_chinese = "";
    }
}

/*
int main( )
{
    Dictionary dict;
    string key;

    do
    {
        cout<<"请输入待查询的关键词（英文）,0000结束："<<endl;
        cin>>key;
        if (key!="0000")
        {
            dict.searchWord(key);
        }
    }
    while(key!="0000");
    cout<<"欢迎再次使用！"<<endl<<endl;
    return 0;
}
*/
