/*
* 在一个二维数组中，每一行都按照从左到右递增的顺序，每一列也按照从上到下递增的顺序
*  给你一个二维数组和整数，请查找整数是否包含在二维数组中
*/

#include <iostream>

bool findInMatrix(int* mat, int row, int col, int target)
{
    bool found = false;
    int curCol = col - 1, curRow = 0;

    while (curCol >= 0 && curRow < row)
    {
        int curVal = mat[curRow * col + curCol];
        if (curVal == target)
            return true;
        else if (curVal > target)
            curCol--;
        else
            curRow++;
    }

    return found;
}

void Test(const char* testName, int* matrix, int rows, int columns, int number, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    bool result = findInMatrix(matrix, rows, columns, number);
    if(result == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数在数组中
void Test1()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    Test("Test1", (int*)matrix, 4, 4, 7, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数不在数组中
void Test2()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    Test("Test2", (int*)matrix, 4, 4, 5, false);
}

int main()
{
    Test1();
    Test2();

    return 0;
}
