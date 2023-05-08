#include "RedBlackTree.h"


int main() {


    RedBlackTree t,t1;//���ź����
    cout << "------------------------------------------------------------------\n"
            "|                      ���������ݽ����ʵ�:                        |\n"
            "|                 ��ʽΪ:���ʡ����롢�÷�                         |\n"
            "------------------------------------------------------------------\n";
    int n;//���ʸ���
    cout << "�����뵥�ʸ���:\n";
    cin >> n;
    for (int i = 1; i <= n; i++) {//���뵥�ʡ����롢�÷������Ҳ�������
        cout << "�������" << i << "�����ʼ��䷭����÷�:\n";
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
            cout << "����ʧ�ܣ������ظ�ֵ��";
    }
    while (1) {
        system("cls");//��գ��ų��˵�
        cout << "---------------------------------------------------------------------\n"
                "|                             ���������                           |\n"
                "|               1.��ѯһ�����ʣ����뵥�ʲ�ѯ��                       |\n"
                "|               2.����һ�����ʣ����뵥�ʡ����롢�÷���               |\n"
                "|               3.ɾ��һ�����ʣ����뵥��ɾ����                       |\n"
                "|               4.չʾ�����ʵ�����                                   |\n"
                "|               5.չʾ��ǰ������ṹ                                 |\n"
                "|               6.���뵥�ʽ�����һ�ú����                           |\n"
                "|               7.չʾ����һ�ź�����ṹ                             |\n"
                "|               8.��������ϲ�                                       |\n"
                "|               9.��������                                           |\n"
                "---------------------------------------------------------------------\n";
        string ord;//����
        cin >> ord;
        if (ord == "1") {//���ҵ���
            string word1;
            cout << "������һ�����ʣ�\n";
            cin >> word1;
            Node* now = t.find(word1);
            if (now != NULL) {//���ҳɹ������
                cout << "\n----------------------------------------------------------------------------------------------------------\n"<<t.find(word1)->value<<"----------------------------------------------------------------------------------------------------------\n";
            }
            else//����ʧ��
                cout << "��Ǹ��δ��ѯ���õ��ʣ�\n";
        }
        else if (ord == "2") {//���뵥��
            string key, translation;
            cout << "������һ�����ʡ����롢�÷���\n";
            cin >> key >> translation;
            string read;
            getline(cin, read, '\n');
            stringstream ss(read);
            vector<string> usage;
            while (ss >> read) {
                usage.push_back(read);
            }
            bool flag = t.insert(word{ key,translation,usage },0);
            if (flag)//����ɹ�
                cout << "����ɹ���\n";
            else//����ʧ��
                cout << "����ʧ�ܣ������ظ����ʣ�\n";
        }
        else if (ord == "3") {//ɾ������
            string word1;
            cout << "������һ�����ʣ�\n";
            cin >> word1;
            bool flag = t.erase(word1);
            if (flag)//ɾ���ɹ�
                cout << "ɾ���ɹ���\n";
            else//ɾ��ʧ��
                cout << "��Ǹ��ɾ��ʧ�ܣ�\n";
        }
        else if (ord == "4") {//��ӡ�ʵ�ṹ
            t.print(t.getRoot());
            cout << "��ӡ�ɹ���\n";
        }
        else if(ord=="5") {//չʾ������ṹ
            t.show();
        }
        else if (ord == "6") {//�γ���һ�ź����
            system("cls");
            cout << "------------------------------------------------------------------\n"
                "|                      ���������ݽ����ʵ�:                        |\n"
                "|                 ��ʽΪ:���ʡ����롢�÷�                         |\n"
                "------------------------------------------------------------------\n";
            cout << "�����뵥�ʸ���:\n";
            cin >> n;
            for (int i = 1; i <= n; i++) {
                cout << "�������" << i << "�����ʼ��䷭����÷�: \n";
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
                    cout << "����ʧ�ܣ������ظ�ֵ��";
            }
        }
        else if (ord == "7") {//չʾ����һ�ú����
            t1.show();
        }
        else if (ord == "8") {//������һ�ź�����ϲ�����ǰ�����
            t.merge(t1);
            cout << "�ϲ��ɹ���\n";
        }else if (ord == "9") {//��������
            cout << "�����ѽ�����\n";
            break;
        }
        else {//��������
            cout << "��������ȷ�����\n";
        }
        cout << "\n\n";
        system("pause");//��ͣ
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
    apple ƻ�� An apple is a round fruit with smooth red, yellow, or green skin and firm white flesh. 
    bird С�� A bird is a creature with feathers and wings. Female birds lay eggs. Most birds can fly.
    cat è Cats are lions, tigers, and other wild animals in the same family. 
    dog �� The British are renowned as a nation of dog lovers.
    egg ���� ...a baby bird hatching from its egg.
    5
    figure ���� It will not be long before the inflation figure starts to fall.
    general ���� The General's visit to Sarajevo is part of preparations for the deployment of extra troops.
    hit ���� Find the exact grip that allows you to hit the ball hard.
    issue ���� Agents will raise the issue of prize-money for next year's world championships.
    journey ���� As per our rule, our bus can not stop at her jouney, if you have anything important, please get off the bus at stop. 


    kind ���� The party needs a different kind of leadership.
    lie ��  There was a child lying on the ground.
    mean ���� Do you mean me?
    note �ʼ� Stevens wrote him a note asking him to come to his apartment.
    object ���� He squinted his eyes as though he were studying an object on the horizon.

    boy �к� He was still just a boy.

 */