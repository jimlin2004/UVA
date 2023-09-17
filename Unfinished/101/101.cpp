#include <stdio.h>

class LinkNode
{
public:
    int val;
    LinkNode* next;
    LinkNode()
    {
        this->val = 0;
        this->next = nullptr;
    }
    LinkNode(int val)
    {
        this->val = val;
        this->next = nullptr;
    }
};

class LinkList
{
public:
    LinkNode* head;
    LinkNode* last;
    LinkList(int val)
    {
        this->head = new LinkNode(val);
        this->last = this->head;
    }
    void update_last()
    {
        if (this->head == nullptr)
        {
            this->last = nullptr;
            return;
        }
        LinkNode* current = this->head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        this->last = current;
    }
    void push_one(int val)
    {
        if (this->head == nullptr)
        {
            this->head = new LinkNode(val);
            this->last = this->head;
            return;
        }
        LinkNode* current = this->head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new LinkNode(val);
        this->last = current->next;
        return;
    }
    void push_node(LinkNode* node)
    {
        if (this->head == nullptr)
        {
            this->head = node;
            this->update_last();
            return;
        }
        this->last->next = node;
        this->update_last();
        return;
    }
};

void initBlocks(LinkList* blocks[], int n)
{
    for (int i = 0; i < n; i++)
    {
        blocks[i] = new LinkList(i);
    }
    return;
}

void return_to_org_pos(LinkList* blocks[], int pos)
{
    LinkNode* current = blocks[pos]->head->next;
    while (current != nullptr)
    {
        blocks[current->val]->push_one(current->val);
    }
    blocks[pos]->head->next = nullptr;
    return;
}

void move_onto(LinkList* blocks[], int a, int b)
{
    return_to_org_pos(blocks, a);
    return_to_org_pos(blocks, b);
    blocks[b]->push_one(a);
    blocks[a]->head = nullptr;
    blocks[a]->last = nullptr;
}

void move_over(LinkList* blocks[], int a, int b)
{
    return_to_org_pos(blocks, a);
    blocks[b]->push_one(a);
    blocks[a]->head = nullptr;
    blocks[a]->last = nullptr;
}

void plie_onto(LinkList* blocks[], int a, int b)
{
    return_to_org_pos(blocks, b);
    blocks[b]->push_node(blocks[a]->head);
    blocks[a]->head = nullptr;
    blocks[a]->last = nullptr;
}

void plie_over(LinkList* blocks[], int a, int b)
{
    blocks[b]->push_node(blocks[a]->head);
    blocks[a]->head = nullptr;
    blocks[a]->last = nullptr;
}

void print_all(LinkList* blocks[], int n)
{
    LinkNode* current = nullptr;
    for (int i = 0; i < n; i++)
    {
        current = blocks[i]->head;
        printf("%d: ", i);
        while (current != nullptr)
        {
            printf("%d ", current->val);
            current = current->next;
        }
        printf("\n");
    }
}

bool check_if_in_same_block(LinkList* blocks[], int a, int b)
{
    LinkNode* current = blocks[b]->head;
    while (current != nullptr)
    {
        if (current->val == a)
            return true;
        current = current->next;
    }
    return false;
}

int main()
{
    int n, a, b;
    LinkList* blocks[25];
    char cmd1[5], cmd2[5];

    while (scanf("%d", &n) != EOF)
    {
        initBlocks(blocks, n);
        scanf("%s", &cmd1);
        while (cmd1[0] != 'q')
        {
            scanf("%d %s %d", &a, &cmd2, &b);
            if (a == b)
            {
                scanf("%s", &cmd1);
                continue;
            }
            if (check_if_in_same_block(blocks, a, b))
            {
                scanf("%s", &cmd1);
                continue;
            }
            if (cmd1[0] == 'm')
            {
                if (cmd2[1] == 'n')
                {
                    move_onto(blocks, a, b);
                }
                else
                {
                    move_over(blocks, a, b);
                }
            }
            else
            {
                if (cmd2[1] == 'n')
                {
                    plie_onto(blocks, a, b);
                }
                else
                {
                    plie_over(blocks, a, b);
                }
            }
            scanf("%s", &cmd1);
        }
        print_all(blocks, n);
    }
}