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

struct word {//����
    string key;//Ӣ�ĵ���
    string translation;//���ķ���
    vector<string> usage;//�÷�����
    //�������캯�����вΡ��޲Ρ����ƹ���
    word() {};
    word(string k, string t, vector<string> u) :key(k), translation(t), usage(u) {};
    word(const word& w) :key(w.key), translation(w.translation), usage(w.usage) {};
    //�����������<��>��==��=��<<
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
        os << "���ʣ�" << w.key << "\n";
        os << "���룺" << w.translation << "\n";
        os << "�÷���"; for (auto& i : w.usage) os << i << " "; os << '\n';
        return os;
    }
};

struct Node {//������ڵ�
    bool color = 0;//�ڵ���ɫ��0Ϊ��ɫ��1Ϊ��ɫ��Ĭ��Ϊ0
    word value;//�ؼ���
    Node* left = NULL; //����
    Node* right = NULL;//�Һ���
    Node* father = NULL;//����
    //����Ϊ�ĸ����캯��
    Node() {};
    Node(word v) :value(v) {};
    Node(word v, Node* f) :value(v), father(f) {};
    Node(word v, Node* f, Node* l, Node* r) :value(v), father(f), left(l), right(r) {};
};

class RedBlackTree {//�������
public:
    RedBlackTree();//���캯��
    ~RedBlackTree();//��������
    Node* find(string value);//����
    bool insert(word value, int ord);//����
    void insertBalance(Node* s);//�������
    bool erase(string value);//ɾ��
    void eraseBalance(Node* x);//ɾ������
    void print(Node* now);//��ӡ
    void show();//����������ʾ
    void leftRotate(Node* z);//����
    void rightRotate(Node* z);//����
    void change(Node* u, Node* v);//��v�滻u
    Node* minNum(Node* x); //�ҵ�x��ʼ��С�ؼ��ʵĽڵ�
    void destory(Node* now);//�ݹ�����������
    void merge(RedBlackTree& t);//������ϲ�
    Node* getRoot();//��ø�
private:
    Node* root;//��
    Node* exNode;//�ⲿ�ڵ�
};