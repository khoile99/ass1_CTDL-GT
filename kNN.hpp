
#include "main.hpp"

template <typename T>
class List
{
public:
    //! Hàm của thầy
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

template <typename T>
class Image : public List<T>
{
private:
    class Node
    {
    public:
        T pointer;
        Node *next;

    public:
        Node(T pointer, Node *next = nullptr) : pointer(pointer), next(next) {}
    };

private:
    Node *head;
    Node *tail;
    int size;

public:
    Image()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~Image()
    {
        this->clear();
    }
    void push_back(T value)
    {
        Node *temp = new Node(value, nullptr);
        if (this->size == 0)
            head = tail = temp;
        else
        {
            this->tail->next = temp;
            tail = temp;
        }
        this->size++;
    }
    void push_front(T value)
    {
        Node *temp = new Node(value);
        if (this->size == 0)
            tail = head = temp;
        else
        {
            temp->next = this->head;
            head = temp;
        }
        this->size++;
    }
    void insert(int index, T value)
    {
        if (index < 0 || index > size)
            return;
        Node *temp = this->head;
        Node *newN = new Node(value);
        if (index == 0)
            this->push_front(value);
        else if (index == this->size)
            this->push_back(value);
        else
        {
            for (int i = 1; i < index; i++)
                temp = temp->next;
            newN->next = temp->next;
            temp->next = newN;
            this->size++;
        }
    }
    void remove(int index)
    {
        if (index < 0 || index >= size)
            return;

        Node *delN;
        Node *temp = head;
        if (this->size == 1)
        {
            delN = head;
            head = tail = nullptr;
        }
        else if (index == 0)
        {
            delN = head;
            head = head->next;
        }
        else
        {
            for (int i = 0; i < index - 1; i++)
                temp = temp->next;
            delN = temp->next;
            temp->next = delN->next;
            if (index == this->size - 1)
            {
                delN = tail;
                tail = temp;
            }
        }
        delete delN;
        this->size--;
    }

    T &get(int index) const
    {
        if (index < 0 || index >= this->size)
            throw out_of_range("get(): Out of range");

        Node *temp = head;
        for (int i = 0; i < index; i++)
            temp = temp->next;

        return temp->pointer;
    }

    int length() const
    {
        return size;
    }

    void clear()
    {
        Node *temp;
        while (head)
        {
            temp = head;
            head = head->next;
            delete temp;
            this->size--;
        }
        tail = head = nullptr;
        this->size = 0;
    }

    void print() const
    {
        if (size == 0)
            cout << "nullptr" << endl;
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            if (i == this->size - 1)
                cout << temp->pointer << endl;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }

    void reverse()
    {
        if (this->size <= 1)
            return;
        Node *curr = this->head;
        Node *prev = this->head->next;
        for (int i = 0; i < this->size - 1; i++)
        {
            Node *temp = prev->next;
            prev->next = curr;
            curr = prev;
            prev = temp;
        }
        this->head->next = nullptr;
        tail = head;
        head = curr;
    }

    void printStartToEnd(int start, int end) const
    {
        Node *temp = head;
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                cout << temp->pointer << endl;
            else
                cout << temp->pointer << " ";
        }
    }

    Image<T> *subList(int start, int end)
    {

        if (this->size <= start)
            return nullptr;
        Image<T> *result = new Image<T>();

        Node *temp = head;
        for (int i = 0; i < start && temp != nullptr; i++)
            temp = temp->next;
        if (temp == nullptr)
            return nullptr;
        for (int i = start; i < this->size && i < end; i++)
        {
            result->push_back(temp->pointer);
            temp = temp->next;
        }
        return result;
    }
    void getArray(T *arr) const
    {
        for (int i = 0; i < this->length(); i++)
        {
            arr[i] = this->get(i);
        }
    }
};

class Dataset
{
private:
    Image<Image<int> *> *data;
    Image<string> *nameCol;

public:
    Dataset()
    {
        this->nameCol = new Image<string>();
        this->data = new Image<Image<int> *>();
    }
    ~Dataset()
    {
        for (int i = 0; i < data->length(); i++)
        {
            data->get(i)->clear();
        }
        for (int i = 0; i < data->length(); i++)
        {
            delete this->data->get(i);
        }
        delete data;
        delete nameCol;
    }
    Dataset(const Dataset &other)
    {
        this->data = new Image<Image<int> *>();
        for (int i = 0; i < other.data->length(); i++)
        {
            Image<int> *newRow = new Image<int>();
            for (int j = 0; j < other.data->get(i)->length(); j++)
            {
                newRow->push_back(other.data->get(i)->get(j));
            }
            this->data->push_back(newRow);
        }
        this->nameCol = new Image<string>();
        for (int i = 0; i < other.nameCol->length(); i++)
        {
            this->nameCol->push_back(other.nameCol->get(i));
        }
    }
    Dataset &operator=(const Dataset &other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->nameCol->clear();
        this->data->clear();

        if (other.data->length() == 0)
        {
            return *this;
        }
        this->nameCol = new Image<string>();
        this->data = new Image<Image<int> *>();
        for (int i = 0; i < other.data->length(); i++)
        {
            Image<int> *newRow = new Image<int>();
            for (int j = 0; j < other.data->get(i)->length(); j++)
            {
                newRow->push_back(other.data->get(i)->get(j));
            }
            this->data->push_back(newRow);
        }

        return *this;
    }
    bool loadFromCSV(const char *fileName)
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            string str;
            int number;
            file >> str;
            for (int i = 0; i < str.length(); i++)
            {
                if (str[i] == ',')
                    str[i] = ' ';
            }
            stringstream ss(str);
            while (ss >> str)
                nameCol->push_back(str);

            while (file >> str)
            {
                for (int i = 0; i < str.length(); i++)
                {
                    if (str[i] == ',')
                        str[i] = ' ';
                }
                stringstream ss(str);
                Image<int> *temp = new Image<int>();
                while (ss >> number)
                    temp->push_back(number);
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void getShape(int &nRows, int &nCols) const
    {
        nRows = this->data->length();
        nCols = this->data->get(0)->length();
    }

    void columns() const
    {
        for (int i = 0; i < this->nameCol->length(); ++i)
        {
            cout << this->nameCol->get(i);
            if (i < nameCol->length() - 1)
                cout << " ";
        }
    }
    void printHead(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0)
            return;
        int totalRows = min(nRows, this->data->length());
        int totalCols = min(nCols, this->nameCol->length());
        for (int j = 0; j < totalCols; j++)
        {
            cout << this->nameCol->get(j);
            if (j < totalCols - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < totalRows; i++)
        {
            for (int j = 0; j < totalCols; j++)
            {
                cout << this->data->get(i)->get(j);
                if (j < totalCols - 1)
                {
                    cout << " ";
                }
            }
            if (i == nRows - 1 || i == totalRows - 1)
            {
                break;
            }
            else
            {
                cout << endl;
            }
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        if (nRows < 0 || nCols <= 0)
            return;
        for (int i = max(0, nameCol->length() - nCols); i < nameCol->length(); i++)
        {
            cout << nameCol->get(i);
            if (i < nameCol->length() - 1)
                cout << " ";
        }
        if (nRows != 0)
            cout << endl;
        for (int i = max(0, data->length() - nRows); i < data->length(); i++)
        {
            Image<int> &rowData = *(data->get(i));
            for (int j = max(0, rowData.length() - nCols); j < rowData.length(); j++)
            {
                cout << rowData.get(j);
                if (j < rowData.length() - 1)
                    cout << " ";
            }
            if (i < data->length() - 1)
                cout << endl;
        }
    }

    bool drop(int axis = 0, int index = 0, string columns = "")
    {
        if (axis == 0)
        {
            if (index < 0 || index >= this->data->length())
            {
                return false;
            }
            this->data->remove(index);
            return true;
        }
        else if (axis == 1)
        {
            int idxCol = -1;
            int col = min(this->nameCol->length(), this->data->get(0)->length());

            if (!columns.empty())
            {
                for (int i = 0; i < this->nameCol->length(); i++)
                {
                    if (this->nameCol->get(i) == columns)
                    {
                        idxCol = i;
                        break;
                    }
                }
            }
            if (idxCol == -1 || col == 0)
            {
                return false;
            }
            this->nameCol->remove(idxCol);
            for (int i = 0; i < this->data->length(); i++)
            {
                this->data->get(i)->remove(idxCol);
            }

            if (this->nameCol->length() == 0)
            {
                for (int i = 0; i < this->data->length(); i++)
                {
                    this->data->get(i)->clear();
                    delete this->data->get(i);
                }
                this->data->clear();
            }
            return true;
        }
        return false;
    }
    Dataset extract(int startRow, int endRow, int startCol, int endCol) const
    {
        Dataset subDataset;
        int row = data->length();
        int col = nameCol->length();

        if (endRow == -1)
            endRow = row - 1;
        if (endCol == -1)
            endCol = col - 1;
        for (int i = startCol; i <= endCol; i++)
        {
            subDataset.nameCol->push_back(nameCol->get(i));
        }

        for (int i = startRow; i <= endRow; i++)
        {
            Image<int> *row = new Image<int>();
            for (int j = startCol; j <= endCol; j++)
            {
                row->push_back(data->get(i)->get(j));
            }
            subDataset.data->push_back(row);
        }
        return subDataset;
    }

    Image<Image<int> *> *getData() const
    {
        return this->data;
    }
    Image<int> *getField(int index)
    {
        return this->data->get(index);
    }

    double score(const Dataset &y_test) const
    {
        if (y_test.data->length() != this->data->length() || y_test.data->length() == 0 || this->data->length() == 0)
        {
            return -1;
        }
        double cnt = 0;
        double size = min(this->data->length(), y_test.data->length());
        for (int i = 0; i < size; i++)
        {
            if (y_test.data->get(i)->get(0) == this->data->get(i)->get(0))
            {
                cnt++;
            }
        }
        return cnt / size;
    }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;

public:
    void sortDistances(double *distances, int *indices, int length)
    {
        for (int i = 0; i < length - 1; ++i)
        {
            for (int j = 0; j < length - i - 1; ++j)
            {
                if (distances[j] > distances[j + 1])
                {
                    std::swap(distances[j], distances[j + 1]);
                    std::swap(indices[j], indices[j + 1]);
                }
            }
        }
    }
    double distanceEuclidean(const Image<int> *x, const Image<int> *y) const
    {
        if (x->length() != y->length())
        {
            throw std::out_of_range("get(): Out of range");
        }

        double distance = 0.0;
        int lengthX = x->length();
        int lengthY = y->length();
        int *arrX = new int[lengthX];
        x->getArray(arrX);

        int *arrY = new int[lengthY];
        y->getArray(arrY);

        int minSize = std::min(lengthX, lengthY);

        for (int i = 0; i < minSize; i++)
        {
            double diff = arrX[i] - arrY[i];
            distance += diff * diff;
        }
        for (int i = minSize; i < lengthX; i++)
        {
            distance += arrX[i] * arrX[i];
        }
        for (int i = minSize; i < lengthY; i++)
        {
            distance += arrY[i] * arrY[i];
        }

        delete[] arrX;
        delete[] arrY;

        return sqrt(distance);
    }
    kNN(int k = 5) : k(5){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset &X_test)
    {
        int testSize = X_test.getData()->length();
        int trainSize = X_train.getData()->length();
        Dataset y_pred;

        if (k > trainSize)
        {
            throw std::out_of_range("get(): Out of range");
        }
        y_pred.getField(5)->push_back(Y_train.getField(5)->get(0));

        for (int i = 0; i < testSize; ++i)
        {
            double *distances = new double[trainSize];
            int *indices = new int[trainSize];

            for (int j = 0; j < trainSize; ++j)
            {
                distances[j] = distanceEuclidean(X_train.getData()->get(j), X_test.getData()->get(i));
                indices[j] = j;
            }

            sortDistances(distances, indices, trainSize);
            int labelCounts[10] = {0};
            for (int m = 0; m < k; ++m)
            {
                int label = Y_train.getData()->get(indices[m])->get(0);
                labelCounts[label]++;
            }
            int mostFrequentLabel = 0;
            int highestCount = labelCounts[0];
            for (int j = 1; j < 10; ++j)
            {
                if (labelCounts[j] > highestCount)
                {
                    highestCount = labelCounts[j];
                    mostFrequentLabel = j;
                }
            }
            Image<int> *predictedLabelImage = new Image<int>();
            predictedLabelImage->push_back(mostFrequentLabel);
            y_pred.getData()->push_back(predictedLabelImage);

            delete[] distances;
            delete[] indices;
        }
        return y_pred;
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test);