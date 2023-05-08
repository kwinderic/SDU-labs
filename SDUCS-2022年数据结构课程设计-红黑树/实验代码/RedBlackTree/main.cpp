#include "RedBlackTree.h"


int main() {


    RedBlackTree t,t1;//两颗红黑树
    cout << "------------------------------------------------------------------\n"
            "|                      请输入数据建立词典:                        |\n"
            "|                 格式为:单词、翻译、用法                         |\n"
            "------------------------------------------------------------------\n";
    int n;//单词个数
    cout << "请输入单词个数:\n";
    cin >> n;
    for (int i = 1; i <= n; i++) {//输入单词、翻译、用法，并且插入红黑树
        cout << "请输入第" << i << "个单词及其翻译和用法:\n";
        string key, translation;
        cin >> key >> translation;
        string read;
        getline(cin, read, '\n');
        stringstream ss(read);
        vector<string> usage;
        while (ss >> read) {
            usage.push_back(read);
        }
        bool f = t.insert(word{ key, translation, usage },0);
        if (f == false)
            cout << "插入失败，存在重复值！";
    }
    while (1) {
        system("cls");//清空，放出菜单
        cout << "---------------------------------------------------------------------\n"
                "|                             请输入命令：                           |\n"
                "|               1.查询一个单词（输入单词查询）                       |\n"
                "|               2.插入一个单词（输入单词、翻译、用法）               |\n"
                "|               3.删除一个单词（输入单词删除）                       |\n"
                "|               4.展示整个词典内容                                   |\n"
                "|               5.展示当前红黑树结构                                 |\n"
                "|               6.输入单词建立另一棵红黑树                           |\n"
                "|               7.展示另外一颗红黑树结构                             |\n"
                "|               8.将红黑树合并                                       |\n"
                "|               9.结束程序                                           |\n"
                "---------------------------------------------------------------------\n";
        string ord;//命令
        cin >> ord;
        if (ord == "1") {//查找单词
            string word1;
            cout << "请输入一个单词：\n";
            cin >> word1;
            Node* now = t.find(word1);
            if (now != NULL) {//查找成功，输出
                cout << "\n----------------------------------------------------------------------------------------------------------\n"<<t.find(word1)->value<<"----------------------------------------------------------------------------------------------------------\n";
            }
            else//查找失败
                cout << "抱歉，未查询到该单词！\n";
        }
        else if (ord == "2") {//插入单词
            string key, translation;
            cout << "请输入一个单词、翻译、用法：\n";
            cin >> key >> translation;
            string read;
            getline(cin, read, '\n');
            stringstream ss(read);
            vector<string> usage;
            while (ss >> read) {
                usage.push_back(read);
            }
            bool flag = t.insert(word{ key,translation,usage },0);
            if (flag)//插入成功
                cout << "插入成功！\n";
            else//插入失败
                cout << "插入失败，存在重复单词！\n";
        }
        else if (ord == "3") {//删除单词
            string word1;
            cout << "请输入一个单词：\n";
            cin >> word1;
            bool flag = t.erase(word1);
            if (flag)//删除成功
                cout << "删除成功！\n";
            else//删除失败
                cout << "抱歉，删除失败！\n";
        }
        else if (ord == "4") {//打印词典结构
            t.print(t.getRoot());
            cout << "打印成功！\n";
        }
        else if(ord=="5") {//展示红黑树结构
            t.show();
        }
        else if (ord == "6") {//形成另一颗红黑树
            system("cls");
            cout << "------------------------------------------------------------------\n"
                "|                      请输入数据建立词典:                        |\n"
                "|                 格式为:单词、翻译、用法                         |\n"
                "------------------------------------------------------------------\n";
            cout << "请输入单词个数:\n";
            cin >> n;
            for (int i = 1; i <= n; i++) {
                cout << "请输入第" << i << "个单词及其翻译和用法: \n";
                string key, translation;
                cin >> key >> translation;
                string read;
                getline(cin, read, '\n');
                stringstream ss(read);
                vector<string> usage;
                while (ss >> read) {
                    usage.push_back(read);
                }
                bool f = t1.insert(word{ key, translation, usage }, 0);
                if (f == false)
                    cout << "插入失败，存在重复值！";
            }
        }
        else if (ord == "7") {//展示另外一棵红黑树
            t1.show();
        }
        else if (ord == "8") {//将另外一颗红黑树合并到当前红黑树
            t.merge(t1);
            cout << "合并成功！\n";
        }else if (ord == "9") {//结束程序
            cout << "程序已结束！\n";
            break;
        }
        else {//错误命令
            cout << "请输入正确的命令！\n";
        }
        cout << "\n\n";
        system("pause");//暂停
    }


}

/*
    10
    1 2 3 4 5 6 7 8 9 10
    5
    4 6 2 9 10
*/
/*
    20
    4 9 5 2 11 13 15 17 19 20 1 3 6 8 7 10 12 16 14 18
    15
    5 2 11 13 15 17 19 20 1 3 6 8 7 10 12
*/
/*
    5
    apple 苹果 An apple is a round fruit with smooth red, yellow, or green skin and firm white flesh. 
    bird 小鸟 A bird is a creature with feathers and wings. Female birds lay eggs. Most birds can fly.
    cat 猫 Cats are lions, tigers, and other wild animals in the same family. 
    dog 狗 The British are renowned as a nation of dog lovers.
    egg 鸡蛋 ...a baby bird hatching from its egg.
    5
    figure 数字 It will not be long before the inflation figure starts to fall.
    general 将军 The General's visit to Sarajevo is part of preparations for the deployment of extra troops.
    hit 击打 Find the exact grip that allows you to hit the ball hard.
    issue 问题 Agents will raise the issue of prize-money for next year's world championships.
    journey 旅行 As per our rule, our bus can not stop at her jouney, if you have anything important, please get off the bus at stop. 


    kind 种类 The party needs a different kind of leadership.
    lie 躺  There was a child lying on the ground.
    mean 意义 Do you mean me?
    note 笔记 Stevens wrote him a note asking him to come to his apartment.
    object 物体 He squinted his eyes as though he were studying an object on the horizon.

    boy 男孩 He was still just a boy.

 */