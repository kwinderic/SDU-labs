#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {//���캯��
    exNode = new Node();//����һ���ⲿ�ڵ�
    exNode->color = 1;
    root = exNode;//���ڵ�ָ���ⲿ�ڵ�
}

RedBlackTree::~RedBlackTree() {//��������
    destory(root);
}

Node* RedBlackTree::find(string value) {//Ѱ��һ���ڵ�
    Node* s = root;
    while (s != exNode) {
        if (s->value.key == value)
            return s;
        if (value < s->value.key) {
            s = s->left;
        }
        else {
            s = s->right;
        }
    }
    return NULL;//û�ҵ�
}

bool RedBlackTree::insert(word value, int ord) {//����ڵ�
    Node* pr = exNode;//s�ĸ���
    Node* s = root;//��ǰ�ڵ�
    while (s != exNode) {
        if (value == s->value)
            return false;//�ҵ���ͬԪ�أ�����
        pr = s;
        if (value < s->value) {//��������
            s = s->left;
        }
        else {//��������
            s = s->right;
        }
    }
    s = new Node(value, pr, exNode, exNode);//�����½ڵ㣬�������Ӷ����ⲿ�ڵ�
    if (pr == exNode) {//����
        root = s;
    }
    else {
        if (value < pr->value) {//��������
            pr->left = s;
        }
        else {//��������
            pr->right = s;
        }
        s->father = pr;
    }
    insertBalance(s);//����ƽ��
    if (ord == 2)
        show();
    return true;//�ҵ�
}

void RedBlackTree::insertBalance(Node* s) {
    Node* uncle;//����ڵ㣬��ǰ�ڵ�ĸ��׵�����һ������
    while (s->father->color == 0) {
        if (s->father == s->father->father->left) {//��ǰΪ���׵�����
            uncle = s->father->father->right;
            if (uncle->color == 0) {//�����
                s->father->color = 0;
                uncle->color = 0;
                s->father->father->color = 1;
                s = s->father->father;
            }
            else {
                if (s == s->father->right) {//�����
                    s = s->father;
                    leftRotate(s);
                }
                s->father->color = 1;//�����
                s->father->father->color = 0;
                rightRotate(s->father->father);
            }
        }
        else {//������һ��
            uncle = s->father->father->left;
            if (uncle->color == 0) {
                s->father->color = 1;
                uncle->color = 1;
                s->father->father->color = 0;
                s = s->father->father;
            }
            else {
                if (s == s->father->left) {
                    s = s->father;
                    rightRotate(s);
                }
                s->father->color = 1;
                s->father->father->color = 0;
                leftRotate(s->father->father);
            }
        }
    }
    root->color = 1;
}

bool RedBlackTree::erase(string value) {//ɾ���ڵ�
    Node* z;
    z = find(value);
    if (z == NULL)//û�ҵ�
        return false;
    if (z != exNode) {//�����ⲿ�ڵ�
        Node* x = exNode;
        Node* y;
        word ycolor;
        if (z->right == exNode) {//������Ϊ�ⲿ�ڵ�
            eraseBalance(z);
            change(z, z->left);
        }
        else {
            y = minNum(z->right);
            z->value = y->value;
            eraseBalance(y);
            change(y, y->right);
        }
    }
    else {
        cout << "ɾ��ʧ�ܣ������ڸýڵ�" << endl;
    }
    return true;
}

void RedBlackTree::eraseBalance(Node* x) {
    while (x != root && x->color != 0) {
        if (x == x->father->left) {//��ǰ�ڵ��ڸ��׽ڵ����
            Node* brother = x->father->right;
            if (brother->color == 0) {//�����
                x->father->color = 0;
                brother->color = 1;
                leftRotate(x->father);
                brother = x->father->right;
            }
            if (brother->left->color == 1 && brother->right->color == 1) {//�����
                brother->color = 0;
                if (x->father->color == 0)
                    x->father->color = 1, x = root;
                else
                    x = x->father;
            }
            else if (brother->right->color == 1) {//�����
                brother->color = 0;
                brother->left->color = 1;
                rightRotate(brother);
                brother = x->father->right;
            }
            else {//�����
                brother->color = x->father->color;
                x->father->color = 1;
                brother->right->color = 1;
                leftRotate(x->father);
                x = root;
            }
        }
        else {//������һ��
            Node* brother = x->father->left;
            if (brother->color == 0) {
                x->father->color = 0;
                brother->color = 1;
                rightRotate(x->father);
                brother = x->father->left;
            }
            if (brother->left->color == 1 && brother->right->color == 1) {
                brother->color = 0;
                if (x->father->color == 0)
                    x->father->color = 1, x = root;
                else
                    x = x->father;
            }
            else if (brother->left->color == 1) {
                brother->color = 0;
                brother->right->color = 1;
                leftRotate(brother);
                brother = x->father->left;
            }
            else {
                brother->color = x->father->color;
                x->father->color = 1;
                brother->left->color = 1;
                rightRotate(x->father);
                x = root;
            }
        }
    }
}

void RedBlackTree::change(Node* u, Node* v) {//��u��λ���滻Ϊv
    if (u->father == exNode) {
        root = v;
    }
    else if (u == u->father->left) {
        u->father->left = v;
    }
    else {
        u->father->right = v;
    }
    v->father = u->father;
}

Node* RedBlackTree::minNum(Node* x) {//�ҵ���ǰ�ڵ�������ֵ��С�Ľڵ�
    if (x->left == exNode)//�ҵ���
        return x;
    return minNum(x->left);
}

/* ����
        zp                zp
        /                 /
       z                 y
      / \      ==>      / \
     lz  y             z  ry
        / \           / \
      ly  ry         lz ly
*/
void RedBlackTree::leftRotate(Node* z) {//��z�ڵ�Ϊ������������ԭ��ͼ����
    Node* y = z->right;
    z->right = y->left;
    if (y->left != exNode) {//y���Ӳ���
        y->left->father = z;
    }
    y->father = z->father;
    if (root == z) {//zΪ���ڵ�
        root = y;
    }
    else if (z == z->father->left) {//zΪ���׵�����
        z->father->left = y;
    }
    else {//zΪ���׵��Һ���
        z->father->right = y;
    }
    y->left = z;
    z->father = y;
}

/* ����
        zp                zp
        /                 /
       z                 y
      / \      ==>      / \
     y  rz             ly  z
    / \                   / \
   ly ry                 ry rz
*/
void RedBlackTree::rightRotate(Node* z) {//��zΪ����������ԭ��ͼ����
    Node* y = z->left;
    z->left = y->right;
    if (y->right != exNode) {//y���Һ��Ӳ�Ϊ��
        y->right->father = z;
    }
    y->father = z->father;
    if (z == root) {//zΪ���ڵ�
        root = y;
    }
    else if (z == z->father->left) {//zΪ���׵�����
        z->father->left = y;
    }
    else {//zΪ���׵��Һ���
        z->father->right = y;
    }
    y->right = z;
    z->father = y;
}

void RedBlackTree::print(Node* now) {//���������ӡ������������Ľڵ㵥��
    if (now->left != exNode)
        print(now->left);
    cout << "\n----------------------------------------------------------------------------------------------------------\n" << now->value << "----------------------------------------------------------------------------------------------------------\n";
    if (now->right != exNode)
        print(now->right);
    //cout << endl;
}

void RedBlackTree::show() {//������������������в�����ʾ
    initgraph(1400, 800);//��ʼ������
    setbkcolor(WHITE);//������ɫΪ��ɫ
    setlinecolor(BLACK);//������ɫΪ��ɫ
    setorigin(700, 30);//��ʼ��ԭ��λ��
    settextcolor(BLACK);//������ɫΪ��ɫ
    cleardevice();//��ջ���
    struct cir {//�ڵ�ṹ��
        Node* node;//������ڵ�
        int x, y;//����
        string s;//����
        bool color;//1Ϊ��ɫ
        int cnt = 1;//�ڼ���
    };
    queue<cir> q;
    cir newNode;
    newNode.x = 0, newNode.y = 0, newNode.color = 1, newNode.s = root->value.key, newNode.node = root;//���ڵ�
    q.push(newNode);
    while (q.size()) {//��α����������ź����
        cir now = q.front();
        q.pop();
        if (now.color == 1)//��ɫ�ڵ�
            setlinecolor(BLACK), settextcolor(BLACK);
        else//��ɫ�ڵ�
            setlinecolor(RED), settextcolor(RED);
        circle(now.x, now.y, 25);//����һ��?��Ϊ�ڵ�
        wchar_t s[100];
        for (int i = 0; i < now.s.length(); i++)
            s[i] = now.s[i];
        s[now.s.length()] = '\0';
        outtextxy(now.x - 23, now.y - 10, s);//�ڽڵ������뵥��
        if (now.node->left != exNode) {//����
            //���½ڵ����Ը�ֵ
            newNode.x = now.x - 1400 / pow(2, now.cnt + 1), newNode.y = now.y + 110, newNode.s = now.node->left->value.key, newNode.node = now.node->left, newNode.color = now.node->left->color, newNode.cnt = now.cnt + 1;
            if (newNode.color == 1)
                setlinecolor(BLACK);
            else
                setlinecolor(RED);
            line(now.x, now.y + 25, newNode.x, newNode.y - 25);
            q.push(newNode);
        }
        if (now.node->right != exNode) {//�Һ���
            //���½ڵ����Ը�ֵ
            newNode.x = now.x + 1400 / pow(2, now.cnt + 1), newNode.y = now.y + 110, newNode.s = now.node->right->value.key, newNode.node = now.node->right, newNode.color = now.node->right->color, newNode.cnt = now.cnt + 1;
            if (newNode.color == 1)
                setlinecolor(BLACK);
            else
                setlinecolor(RED);
            line(now.x, now.y + 25, newNode.x, newNode.y - 25);
            q.push(newNode);
        }
    }
    /*     EndBatchDraw();*/
    _getwch();//��ͣ�������������
    closegraph();//�رջ���
}

void RedBlackTree::destory(Node* now) {//�������ź�������ͷ��ڴ�ռ�
    if (now == exNode)
        return;
    if (now->left != exNode)//������
        destory(now->left);
    else
        destory(now->right);//���Һ���
    delete now;
    now = NULL;
}

void RedBlackTree::merge(RedBlackTree& t)//������ϲ�
{
    while (t.getRoot()->left->value.key != "" && t.getRoot()->right->value.key != "") {//��t�Ľڵ�Ӹ��ڵ㿪ʼȡ�����Ҳ��뵽��ǰ�ĺ����
        //cout << "!" << t.getRoot()->left->value.key << " " << t.getRoot()->right->value.key << endl;
        insert(t.getRoot()->value, 1);
        t.erase(t.getRoot()->value.key);
        /*       t.show();*/
    }
    if (t.getRoot()->left->value.key != "") {//�����ʣ��Ľڵ�ȡ������
        insert(t.getRoot()->left->value, 1);
        insert(t.getRoot()->value, 1);
    }
    else if (t.getRoot()->right->value.key != "") {
        insert(t.getRoot()->right->value, 1);
        insert(t.getRoot()->value, 1);
    }
    else {
        insert(t.getRoot()->value, 1);
    }
}

Node* RedBlackTree::getRoot()//���ظ��ڵ�
{
    return root;
}
