#pragma once
#include <string>
#include<iostream>
#include<cstdio>
#include<fstream>
#include<easyx.h>
#include<graphics.h>
#include<queue>
#include <windows.h>
#include<sstream>
using namespace std;

struct word {//单词
    string key;//英文单词
    string translation;//中文翻译
    vector<string> usage;//用法例句
    //三个构造函数：有参、无参、复制构造
    word() {};
    word(string k, string t, vector<string> u) :key(k), translation(t), usage(u) {};
    word(const word& w) :key(w.key), translation(w.translation), usage(w.usage) {};
    //重载运算符：<、>、==、=、<<
    bool operator < (const word& w) {
        return this->key < w.key;
    }
    bool operator > (const word& w) {
        return this->key > w.key;
    }
    bool operator == (const word& w) {
        return this->key == w.key;
    }
    void operator = (const word& w) {
        this->key = w.key;
    }
    friend ostream& operator << (ostream& os, const word& w) {
        os << "单词：" << w.key << "\n";
        os << "翻译：" << w.translation << "\n";
        os << "用法："; for (auto& i : w.usage) os << i << " "; os << '\n';
        return os;
    }
};

struct Node {//红黑树节点
    bool color = 0;//节点颜色，0为红色，1为黑色，默认为0
    word value;//关键词
    Node* left = NULL; //左孩子
    Node* right = NULL;//右孩子
    Node* father = NULL;//父亲
    //以下为四个构造函数
    Node() {};
    Node(word v) :value(v) {};
    Node(word v, Node* f) :value(v), father(f) {};
    Node(word v, Node* f, Node* l, Node* r) :value(v), father(f), left(l), right(r) {};
};

class RedBlackTree {//红黑树类
public:
    RedBlackTree();//构造函数
    ~RedBlackTree();//析构函数
    Node* find(string value);//查找
    bool insert(word value, int ord);//插入
    void insertBalance(Node* s);//插入调整
    bool erase(string value);//删除
    void eraseBalance(Node* x);//删除调整
    void print(Node* now);//打印
    void show();//基本操作演示
    void leftRotate(Node* z);//左旋
    void rightRotate(Node* z);//右旋
    void change(Node* u, Node* v);//将v替换u
    Node* minNum(Node* x); //找到x开始最小关键词的节点
    void destory(Node* now);//递归销毁整棵树
    void merge(RedBlackTree& t);//红黑树合并
    Node* getRoot();//获得根
private:
    Node* root;//根
    Node* exNode;//外部节点
};