#include <iostream>

void enterCols(int32_t&);
void enterRows(int32_t&);
void fillMemoryMatrix(int32_t**&, int32_t, int32_t);
void fillSpiralMatrix(int32_t**, int32_t, int32_t);
void printMatrix(int32_t**, int32_t, int32_t);
void sumPubDiagonal(int32_t**, int32_t, int32_t);
void freeMatrix(int32_t**, int32_t);

int main()
{
    int32_t cols{};
    int32_t rows{};
    int32_t** mtr = nullptr;

    enterCols(cols);
    enterRows(rows);
    try{
        if (cols != rows)
        {
            throw std::invalid_argument("Not equal cols and rows.");
        }
        fillMemoryMatrix(mtr, cols, rows);
        fillSpiralMatrix(mtr, rows, cols);
        printMatrix(mtr, rows, cols);
        std::cout << std::endl;
        sumPubDiagonal(mtr, cols, rows);
        freeMatrix(mtr, rows);
    }
    catch (std::invalid_argument e){
        std::cout << e.what();

    }
    return 0;
}

void fillMemoryMatrix(int32_t**& mtr, int32_t cols, int32_t rows)
{
    mtr = new int32_t * [rows];

    for (int32_t i = 0; i < rows; ++i)
    {
        mtr[i] = new int32_t[cols];
    }
}

void enterCols(int32_t& cols)
{
    std::cout << "Enter cols: ";
    std::cin >> cols;
}

void enterRows(int32_t& rows)
{
    std::cout << "Enter rows: ";
    std::cin >> rows;
}

void fillSpiralMatrix(int32_t** mtr, int32_t rows, int32_t cols)
{
    int32_t naturalNum = 1;
    int32_t left = 0, right = cols - 1;
    int32_t top = 0, bottom = rows - 1;

    while (left <= right && top <= bottom)
    {
        for (int32_t i = left; i <= right; ++i)
        {
            mtr[top][i] = naturalNum++;
        }
        top++;

        for (int32_t i = top; i <= bottom; ++i)
        {
            mtr[i][right] = naturalNum++;
        }
        right--;

        if (top <= bottom)
        {
            for (int32_t i = right; i >= left; --i)
            {
                mtr[bottom][i] = naturalNum++;
            }
            bottom--;
        }
        if (left <= right)
        {
            for (int32_t i = bottom; i >= top; --i)
            {
                mtr[i][left] = naturalNum++;
            }
            left++;
        }
    }
}
void sumPubDiagonal(int32_t** mtr, int32_t cols, int32_t rows)
{
    int32_t summ{};
    for (int32_t i = 0; i < rows; ++i)
    {
        summ += mtr[i][cols - 1 - i]; 
    }
    std::cout << summ;
}

void printMatrix(int32_t** mtr, int32_t rows, int32_t cols)
{
    for (int32_t i = 0; i < rows; ++i)
    {
        for (int32_t j = 0; j < cols; ++j)
        {
            std::cout << mtr[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void freeMatrix(int32_t** mtr, int32_t rows)
{
    for (int32_t i = 0; i < rows; ++i)
    {
        delete[] mtr[i];
    }
    delete[] mtr;
}






