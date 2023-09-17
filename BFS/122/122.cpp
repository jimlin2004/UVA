#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    Node* l = nullptr, *r = nullptr;
    int val = -1;
};

Node* root = nullptr;
bool error = false; // 重複賦值在同一個node

void insert(Node* root, int val, string direct)
{
    if (direct.empty())
    {
        if (root->val != -1)
            error = true;
        else
            root->val = val;
        return;
    }
    if (direct.back() == 'L')
    {
        if (root->l == nullptr)
            root->l = new Node();
        direct.pop_back();
        insert(root->l, val, direct);
    }
    else
    {
        if (root->r == nullptr)
            root->r = new Node();
        direct.pop_back();
        insert(root->r, val, direct);
    }
}

void slove(const string& str)
{
    int val = stoi(str.substr(1, str.find(',')));
    int count = str.size() - str.find(',') - 2;
    string direct = str.substr(str.find(',') + 1, count);
    reverse(direct.begin(), direct.end());
    insert(root, val, direct);
    return;
}

void bfs()
{
    queue<Node*> q;
    q.push(root);
    vector<int> res;
    Node* current;
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        if (current->val == -1 || error)
        {
            printf("not complete\n");
            return;
        }
        res.emplace_back(current->val);
        if (current->l != nullptr)
            q.push(current->l);
        if (current->r != nullptr)
            q.push(current->r);
    }
    bool flag = false;
    for (int val: res)
    {
        if (flag)
            printf(" ");
        else
            flag = true;
        printf("%d", val);
    }
    puts("");
}

void destroyTree(Node* root)
{
    if (root == nullptr)
        return;
    if (root->l != nullptr)
        destroyTree(root->l);
    if (root->r != nullptr)
        destroyTree(root->r);
    delete root;
}

int main()
{
    string input;
    while (cin >> input)
    {
        destroyTree(root);
        root = new Node();
        error = false;
        slove(input);

        while (cin >> input)
        {
            if (input == "()")
                break;
            slove(input);
        }
        bfs();
    }
    return 0;
}