#include "kNN.hpp"

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
    if (X.getData()->length() != Y.getData()->length() || test_size >= 1 || test_size <= 0)
        return;

    int nRow = X.getData()->length();
    int rowSplit = (int)(nRow * (1 - test_size));

    

    X_train = X.extract(0, rowSplit - 1, 0, -1);
    Y_train = Y.extract(0, rowSplit - 1, 0, -1);

    X_test = X.extract(rowSplit, -1, 0, -1);
    Y_test = Y.extract(rowSplit, -1, 0, -1);
}
    // Dataset y_pred;
    // int test = X_train.getData()->length();
    // double *distances = new double[test];
    // int *indices = new int[test];

    // for (int i = 0; i < this->data->length(); ++i)
    // {
    //     for (int j = 0; j < test; ++j)
    //     {
    //         distances[j] = this->data->get(i)->distanceEuclidean(X_train.getData()->get(j));
    //         indices[j] = j;
    //     }

    //     for (int m = 0; m < test - 1; ++m)
    //     {
    //         for (int n = 0; n < test - m - 1; ++n)
    //         {
    //             if (distances[n] > distances[n + 1])
    //             {
    //                 std::swap(distances[n], distances[n + 1]);
    //                 std::swap(indices[n], indices[n + 1]);
    //             }
    //         }
    //     }
    //     int labelCounts[10] = {0};
    //     for (int m = 0; m < k; ++m)
    //     {
    //         int label = Y_train.getData()->get(indices[m])->get(0);
    //         labelCounts[label]++;
    //     }

    //     int mostFrequentLabel = 0;
    //     int highestCount = 0;

    //     for (int j = 0; j < 10; ++j)
    //     {
    //         if (labelCounts[j] > highestCount)
    //         {
    //             highestCount = labelCounts[j];
    //             mostFrequentLabel = j;
    //         }
    //         else if (labelCounts[j] == highestCount && mostFrequentLabel > j)
    //         {
    //             mostFrequentLabel = j;
    //         }
    //     }
    //     Image<int> *predictedLabelList = new Image<int>();
    //     predictedLabelList->push_back(mostFrequentLabel);
    //     y_pred.getData()->push_back(predictedLabelList);
    //         }

    //         delete[] distances;
    //         delete[] indices;
    //     return ypred;