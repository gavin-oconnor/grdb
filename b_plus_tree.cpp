

template <typename T, int ORDER>
class BPlusTreeNode
{
public:
    BPlusTreeNode<T, ORDER> *children[ORDER];
    T keys[ORDER - 1];
    int n;
    bool is_leaf;
    BPlusTreeNode<T, ORDER> *next_leaf;

    BPlusTreeNode(bool is_leaf)
    {
        this->is_leaf = is_leaf;
        n = 0;
        next_leaf = nullptr;
        for (int i = 0; i < ORDER; i++)
        {
            children[i] = nullptr;
        }
    }
    ~BPlusTreeNode()
    {
        for (int i = 0; i < ORDER; i++)
        {
            if (children[i] != nullptr)
            {
                delete children[i];
            }
        }
    }
};

template <typename T, int ORDER>
class BPlusTree
{
public:
    BPlusTreeNode<T, ORDER> *root;
    BPlusTree()
    {
        root = new BPlusTreeNode<T, ORDER>(true);
    }
    ~BPlusTree()
    {
        delete root;
    }
    void insert(T key);
    void remove(T key);
};
