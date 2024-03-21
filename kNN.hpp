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
    ~List() { clear(); };
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
private:
    List<List<int> *> *data;

public:
    Dataset()
    {
        data = new List<List<int> *>();
    };
    ~Dataset()
    {
        clear();
    };
    Dataset(const Dataset &other)
    {
        // Initialize data as a new list
        data = new List<List<int> *>();

        // Iterate through each row of the other dataset and copy its elements
        for (int i = 0; i < other.data->length(); ++i)
        {
            List<int> *newRow = new List<int>();
            List<int> *otherRow = other.data->get(i);

            // Copy each element of the row
            for (int j = 0; j < otherRow->length(); ++j)
            {
                newRow->push_back(otherRow->get(j));
            }

            // Add the copied row to the data list
            data->push_back(newRow);
        }
    };
    Dataset &operator=(const Dataset &other)
    {
        // Check for self-assignment
        if (this != &other)
        {
            // Clear the existing data in the current object
            clear();

            // Iterate through each row of the other dataset and copy its elements
            for (int i = 0; i < other.data->length(); ++i)
            {
                List<int> *newRow = new List<int>();
                List<int> *otherRow = other.data->get(i);

                // Copy each element of the row
                for (int j = 0; j < otherRow->length(); ++j)
                {
                    newRow->push_back(otherRow->get(j));
                }

                // Add the copied row to the data list
                data->push_back(newRow);
            }
        }

        return *this; // Return a reference to the current object
    };
    void clear()
    {
        // Iterate over the data list and delete each list of integers
        ListNode<List<int> *> *current = data->head;
        while (current)
        {
            delete current->data;
            ListNode<List<int> *> *temp = current;
            current = current->next;
            delete temp;
        }
        data->head = nullptr;
        data->size = 0;
    }
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
    void printHead(int nRows = 5, int nCols = 5) const
    {
        nRows = std::min(nRows, data->length());
        nCols = std::min(nCols, data->get(0)->length());
        for (int i = 0; i < nRows; ++i)
        {
            for (int j = 0; j < nCols; ++j)
            {
                if (j == nCols - 1)
                    std::cout << data->get(i)->get(j);
                else
                    std::cout << data->get(i)->get(j) << " ";
            }
            std::cout << std::endl;
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        int rowLength = data->length();
        int colLength = data->get(0)->length();
        nRows = std::min(nRows, rowLength);
        nCols = std::min(nCols, colLength);
        for (int i = rowLength - nRows; i < rowLength; ++i)
        {
            for (int j = colLength - nCols; j < colLength; ++j)
            {
                std::cout << data->get(i)->get(j) << " ";
            }
            std::cout << std::endl;
        }
    }
    void getShape(int &nRows, int &nCols) const
    {
        if (data->length() > 0)
        {
            nRows = data->length();
            nCols = data->get(0)->length();
        }
        else
        {
            nRows = 0;
            nCols = 0;
        }
    };
    // void columns() const;
    // bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        // Get the total number of rows and columns in the dataset
        int totalRows = data->length();
        int totalCols = (totalRows > 0) ? data->get(0)->length() : 0;

        // Adjust endRow and endCol if they are -1
        if (endRow == -1)
        {
            endRow = totalRows - 1;
        }
        if (endCol == -1)
        {
            endCol = totalCols - 1;
        }

        // Create a new dataset to store the extracted data
        Dataset subset;

        // Ensure startRow, endRow, startCol, and endCol are within valid range
        startRow = std::max(0, std::min(startRow, totalRows - 1));
        endRow = std::max(0, std::min(endRow, totalRows - 1));
        startCol = std::max(0, std::min(startCol, totalCols - 1));
        endCol = std::max(0, std::min(endCol, totalCols - 1));

        // Extract the subset of data
        for (int i = startRow; i <= endRow; ++i)
        {
            List<int> *row = new List<int>();
            for (int j = startCol; j <= endCol; ++j)
            {
                row->push_back(data->get(i)->get(j));
            }
            subset.data->push_back(row);
        }

        return subset;
    };
    List<List<int> *> *getData() const
    {
        return data;
    };
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