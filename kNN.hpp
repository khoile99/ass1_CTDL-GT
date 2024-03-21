#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template <typename T>
class ListNode
{
public:
    T data;
    ListNode *next;
    ListNode(T value) : data(value), next(nullptr) {}
};

template <typename T>
class List
{
public:
    ListNode<T> *head;
    int size;
    // ~List() { clear(); };
    List()
    {
        head = nullptr;
        size = 0;
    }
    void push_back(T value)
    {
        ListNode<T> *newNode = new ListNode<T>(value);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            ListNode<T> *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    };
    void push_front(T value)
    {
        ListNode<T> *newNode = new ListNode<T>(value);
        newNode->next = head;
        head = newNode;
        size++;
    };
    void insert(int index, T value)
    {
        if (index < 0 || index > size)
        {
            return;
        }
        if (index == 0)
        {
            push_front(value);
        }
        else if (index == size)
        {
            push_back(value);
        }
        else
        {
            ListNode<T> *newNode = new ListNode<T>(value);
            ListNode<T> *temp = head;
            for (int i = 0; i < index - 1; ++i)
            {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            size++;
        }
    };
    void remove(int index)
    {
        if (index < 0 || index >= size)
        {
            return;
        }
        ListNode<T> *temp = head;
        if (index == 0)
        {
            head = head->next;
            delete temp;
        }
        else
        {
            for (int i = 0; i < index - 1; ++i)
            {
                temp = temp->next;
            }
            ListNode<T> *nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        }
        size--;
    };
    T &get(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Out of range");
        }
        ListNode<T> *temp = head;
        for (int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        return temp->data;
    };
    int length() { return size; };
    void clear()
    {
        while (head != nullptr)
        {
            ListNode<T> *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    };
    void print() const
    {
        ListNode<T> *temp = head;
        while (temp)
        {
            if (temp->next == nullptr)
                cout << temp->data;
            else
                cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    };
    void reverse()
    {
        ListNode<T> *prev = nullptr;
        ListNode<T> *current = head;
        ListNode<T> *next = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    };
};

class Dataset
{
public:
    List<List<int> *> *data;
    Dataset()
    {
        data = new List<List<int> *>();
    };
    // ~Dataset();
    // Dataset(const Dataset &other);
    // Dataset &operator=(const Dataset &other);
    bool loadFromCSV(const char *fileName)
    {
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line))
        {
            List<int> *row = new List<int>();
            std::stringstream ss(line);
            int value;
            while (ss >> value)
            {
                row->push_back(value);
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
            }
            this->data->push_back(row);
        }

        file.close();
        return true;
    };
    // void printHead(int nRows = 5, int nCols = 5) const;
    // void printTail(int nRows = 5, int nCols = 5) const;
    // void getShape(int &nRows, int &nCols) const;
    // void columns() const;
    // bool drop(int axis = 0, int index = 0, std::string columns = "");
    // Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    // List<List<int> *> *getData() const;
};

class kNN
{
private:
    int k;
    // You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset &X_train, const Dataset &y_train);
    Dataset predict(const Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test);

// Please add more or modify as needed