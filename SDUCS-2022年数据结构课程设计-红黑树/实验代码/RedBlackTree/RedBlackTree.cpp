#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {//构造函数
    exNode = new Node();//申请一个外部节点
    exNode->color = 1;
    root = exNode;//根节点指向外部节点
}

RedBlackTree::~RedBlackTree() {//析构函数
    destory(root);
}

Node* RedBlackTree::find(string value) {//寻找一个节点
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
    return NULL;//没找到
}

bool RedBlackTree::insert(word value, int ord) {//插入节点
    Node* pr = exNode;//s的父亲
    Node* s = root;//当前节点
    while (s != exNode) {
        if (value == s->value)
            return false;//找到相同元素，返回
        pr = s;
        if (value < s->value) {//在左子树
            s = s->left;
        }
        else {//在右子树
            s = s->right;
        }
    }
    s = new Node(value, pr, exNode, exNode);//申请新节点，两个孩子都是外部节点
    if (pr == exNode) {//空树
        root = s;
    }
    else {
        if (value < pr->value) {//在左子树
            pr->left = s;
        }
        else {//在右子树
            pr->right = s;
        }
        s->father = pr;
    }
    insertBalance(s);//插入平衡
    if (ord == 2)
        show();
    return true;//找到
}

void RedBlackTree::insertBalance(Node* s) {
    Node* uncle;//叔叔节点，当前节点的父亲的另外一个孩子
    while (s->father->color == 0) {
        if (s->father == s->father->father->left) {//当前为父亲的左孩子
            uncle = s->father->father->right;
            if (uncle->color == 0) {//情况三
                s->father->color = 0;
                uncle->color = 0;
                s->father->father->color = 1;
                s = s->father->father;
            }
            else {
                if (s == s->father->right) {//情况四
                    s = s->father;
                    leftRotate(s);
                }
                s->father->color = 1;//情况五
                s->father->father->color = 0;
                rightRotate(s->father->father);
            }
        }
        else {//镜像另一半
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

bool RedBlackTree::erase(string value) {//删除节点
    Node* z;
    z = find(value);
    if (z == NULL)//没找到
        return false;
    if (z != exNode) {//不是外部节点
        Node* x = exNode;
        Node* y;
        word ycolor;
        if (z->right == exNode) {//右子树为外部节点
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
        cout << "删除失败，不存在该节点" << endl;
    }
    return true;
}

void RedBlackTree::eraseBalance(Node* x) {
    while (x != root && x->color != 0) {
        if (x == x->father->left) {//当前节点在父亲节点左侧
            Node* brother = x->father->right;
            if (brother->color == 0) {//情况三
                x->father->color = 0;
                brother->color = 1;
                leftRotate(x->father);
                brother = x->father->right;
            }
            if (brother->left->color == 1 && brother->right->color == 1) {//情况四
                brother->color = 0;
                if (x->father->color == 0)
                    x->father->color = 1, x = root;
                else
                    x = x->father;
            }
            else if (brother->right->color == 1) {//情况五
                brother->color = 0;
                brother->left->color = 1;
                rightRotate(brother);
                brother = x->father->right;
            }
            else {//情况六
                brother->color = x->father->color;
                x->father->color = 1;
                brother->right->color = 1;
                leftRotate(x->father);
                x = root;
            }
        }
        else {//镜像另一半
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

void RedBlackTree::change(Node* u, Node* v) {//将u的位置替换为v
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

Node* RedBlackTree::minNum(Node* x) {//找到当前节点子树中值最小的节点
    if (x->left == exNode)//找到了
        return x;
    return minNum(x->left);
}

/* 左旋
        zp                zp
        /                 /
       z                 y
      / \      ==>      / \
     lz  y             z  ry
        / \           / \
      ly  ry         lz ly
*/
void RedBlackTree::leftRotate(Node* z) {//以z节点为中心左旋，其原理图如上
    Node* y = z->right;
    z->right = y->left;
    if (y->left != exNode) {//y左孩子不空
        y->left->father = z;
    }
    y->father = z->father;
    if (root == z) {//z为根节点
        root = y;
    }
    else if (z == z->father->left) {//z为父亲的左孩子
        z->father->left = y;
    }
    else {//z为父亲的右孩子
        z->father->right = y;
    }
    y->left = z;
    z->father = y;
}

/* 左旋
        zp                zp
        /                 /
       z                 y
      / \      ==>      / \
     y  rz             ly  z
    / \                   / \
   ly ry                 ry rz
*/
void RedBlackTree::rightRotate(Node* z) {//以z为中心右旋，原理图如上
    Node* y = z->left;
    z->left = y->right;
    if (y->right != exNode) {//y的右孩子不为空
        y->right->father = z;
    }
    y->father = z->father;
    if (z == root) {//z为根节点
        root = y;
    }
    else if (z == z->father->left) {//z为父亲的左孩子
        z->father->left = y;
    }
    else {//z为父亲的右孩子
        z->father->right = y;
    }
    y->right = z;
    z->father = y;
}

void RedBlackTree::print(Node* now) {//先序遍历打印出整个红黑树的节点单词
    if (now->left != exNode)
        print(now->left);
    cout << "\n----------------------------------------------------------------------------------------------------------\n" << now->value << "----------------------------------------------------------------------------------------------------------\n";
    if (now->right != exNode)
        print(now->right);
    //cout << endl;
}

void RedBlackTree::show() {//画出整个红黑树，进行操作演示
    initgraph(1400, 800);//初始化画布
    setbkcolor(WHITE);//画布颜色为白色
    setlinecolor(BLACK);//线条颜色为黑色
    setorigin(700, 30);//初始化原点位置
    settextcolor(BLACK);//字体颜色为黑色
    cleardevice();//清空画布
    struct cir {//节点结构体
        Node* node;//红黑树节点
        int x, y;//坐标
        string s;//单词
        bool color;//1为黑色
        int cnt = 1;//第几行
    };
    queue<cir> q;
    cir newNode;
    newNode.x = 0, newNode.y = 0, newNode.color = 1, newNode.s = root->value.key, newNode.node = root;//根节点
    q.push(newNode);
    while (q.size()) {//层次遍历画出整颗红黑树
        cir now = q.front();
        q.pop();
        if (now.color == 1)//红色节点
            setlinecolor(BLACK), settextcolor(BLACK);
        else//黑色节点
            setlinecolor(RED), settextcolor(RED);
        circle(now.x, now.y, 25);//画出一个?作为节点
        wchar_t s[100];
        for (int i = 0; i < now.s.length(); i++)
            s[i] = now.s[i];
        s[now.s.length()] = '\0';
        outtextxy(now.x - 23, now.y - 10, s);//在节点内填入单词
        if (now.node->left != exNode) {//左孩子
            //给新节点属性赋值
            newNode.x = now.x - 1400 / pow(2, now.cnt + 1), newNode.y = now.y + 110, newNode.s = now.node->left->value.key, newNode.node = now.node->left, newNode.color = now.node->left->color, newNode.cnt = now.cnt + 1;
            if (newNode.color == 1)
                setlinecolor(BLACK);
            else
                setlinecolor(RED);
            line(now.x, now.y + 25, newNode.x, newNode.y - 25);
            q.push(newNode);
        }
        if (now.node->right != exNode) {//右孩子
            //给新节点属性赋值
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
    _getwch();//暂停，按任意键继续
    closegraph();//关闭画布
}

void RedBlackTree::destory(Node* now) {//销毁整颗红黑树，释放内存空间
    if (now == exNode)
        return;
    if (now->left != exNode)//有左孩子
        destory(now->left);
    else
        destory(now->right);//有右孩子
    delete now;
    now = NULL;
}

void RedBlackTree::merge(RedBlackTree& t)//红黑树合并
{
    while (t.getRoot()->left->value.key != "" && t.getRoot()->right->value.key != "") {//将t的节点从根节点开始取出并且插入到当前的红黑树
        //cout << "!" << t.getRoot()->left->value.key << " " << t.getRoot()->right->value.key << endl;
        insert(t.getRoot()->value, 1);
        t.erase(t.getRoot()->value.key);
        /*       t.show();*/
    }
    if (t.getRoot()->left->value.key != "") {//把最后剩余的节点取出插入
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

Node* RedBlackTree::getRoot()//返回根节点
{
    return root;
}
