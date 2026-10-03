// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
// Lab_ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

// 5 вариант

#include "Rus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

// просто чтобы не запутаться
struct Matrix
{
    int** rows;
};

// очистка буфера
void ClearBuffer()
{
    int c;
    while ((c = getwchar()) != '\n' && c != EOF);
}

// 1 задание
void MassivInput()
{
    wprintf(L"Введите длину массива: ");

    int len = 0;

    if (input(L"%d", &len))
        return;

    // динамический массив
    int* mas = (int*)malloc(len * sizeof(int));

    if (mas == NULL)
    {
        wprintf(L"Ошибка выделения памяти\n");
        return;
    }

    wprintf(L"Введите элементы массива:\n");

    for (int i = 0; i < len; i++)
        if (input(L"%d", &mas[i]))
            continue;

    int sum = 0;

    for (int i = 0; i < len; i++)
    {
        wprintf(L"%d ", mas[i]);

        if (mas[i] % 2 != 0)
            sum += mas[i];
    }

    // освобождение памяти и обнуление указателя
    free(mas);
    mas = NULL;

    wprintf(L"\nСумма эелементов: %d\n", sum);
}

// 2 задание
void MatrixInput()
{
    int rows;
    int cols;

    wprintf(L"Введите размер матрицы AxB: ");
    if (input(L"%d%d", &rows, &cols))
        return;

    struct Matrix mat;

    mat.rows = (int**)malloc(rows * sizeof(int*));
    if (mat.rows == NULL)
    {
        wprintf(L"Ошибка выделения памяти\n");
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        mat.rows[i] = (int*)malloc(cols * sizeof(int));
        if (mat.rows[i] == NULL)
        {
            wprintf(L"Ошибка выделения памяти\n");
            return;
        }
    }

    wprintf(L"\nВид матрицы %d x %d: \n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        wprintf(L"[ ");

        for (int j = 0; j < cols; j++)
        {
            if (j > 0)
                wprintf(L" | #");
            else
                wprintf(L"#");
        }

        wprintf(L" ]\n");
    }

    wprintf(L"\nВведите целочисленные значения в матрицу по строкам:\n");

    for (int i = 0; i < rows; i++)
    {
        wprintf(L"Введите строку %d:\n", i);

        for (int j = 0; j < cols; j++)
        {
            if (input(L"%d", &mat.rows[i][j]))
                return;
        }
    }

    wprintf(L"\nВведённая матрица:\n");
    for (int i = 0; i < rows; i++)
    {
        wprintf(L"[ ");

        for (int j = 0; j < cols; j++)
        {
            if (j > 0)
                wprintf(L" | %d", mat.rows[i][j]);
            else
                wprintf(L"%d", mat.rows[i][j]);
        }

        wprintf(L" ]\n");
    }

    // поиск максимума в нечётных столбцах
    for (int j = 0; j < cols; j++)
    {
        if (j % 2 != 0)
        {
            int maxRow = 0;
            for (int i = 0; i < rows; i++)
            {
                if (mat.rows[i][j] > mat.rows[maxRow][j])
                    maxRow = i;
            }

            wprintf(L"Максимум: %d, в строке:%d, столбце:%d\n", mat.rows[maxRow][j], maxRow, j);
        }
    }

    for (int i = 0; i < rows; i++)
        free(mat.rows[i]);

    free(mat.rows);
}

// 3 задание
void StringWordCount()
{
    wchar_t string[150];

    ClearBuffer();

    wprintf(L"Введите строку(максимум 150 символов):\n");

    if (input(L"%149[^\n]", string))
        return;

    wprintf(L"Ввод: %ls\n", string);

    int wordsCount = 0;
    int inWord = 0;

    for (int i = 0; i < 150; i++)
    {
        wchar_t c = string[i];

        if (c == '\0')
            break;

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
        {
            inWord = 0;
        }
        else
        {
            if (!inWord)
            {
                inWord = 1;

                switch (c)
                {
                    // русские гласные
                    case L'а': case L'А': case L'е': case L'Е': case L'ё': case L'Ё':
                    case L'и': case L'И': case L'о': case L'О': case L'у': case L'У':
                    case L'ы': case L'Ы': case L'э': case L'Э': case L'ю': case L'Ю':
                    case L'я': case L'Я':
                    
                    // английские гласные
                    case L'a': case L'A': case L'e': case L'E': case L'i': case L'I':
                    case L'o': case L'O': case L'u': case L'U': case L'y': case L'Y':
                        break;

                    default:
                        if (iswalpha(c))
                        {
                            wordsCount++;
                        }
                        break;
                }
            }
        }
    }

    wprintf(L"Количество слов начинающихся с согласной: %d\n", wordsCount);
}

// 4 задание
void StringWordSwitch()
{
    wchar_t string[150];

    ClearBuffer();

    wprintf(L"Введите строку(максимум 150 символов):\n");

    if (input(L"%149[^\n]", string))
        return;

    wprintf(L"Ввод: %ls\n", string);

    wchar_t word1[10] = L"";
    wchar_t word2[10] = L"";

    ClearBuffer();

    wprintf(L"Введите слово L1(максимум 10 символов): ");

    if (input(L"%9[^\n]", word1))
        return;

    ClearBuffer();

    wprintf(L"Введите слово L2(максимум 10 символов): ");

    if (input(L"%9[^\n]", word2))
        return;
    
    // подсчёт количества введённых слов в тексте через буфер
    wchar_t buf[20];    // буфер для слова

    int bufIdx = 0,     // индекс текущей буквы в буфере слова
        inWord = 0,     // флаг если внутри слова
        count1 = 0,     // счётчики количества слов
        count2 = 0;

    for (int i = 0; ; i++)
    {
        wchar_t c = string[i];

        if (c == L' ' || c == L'\t' || c == L'\n' || c == L'\r' || c == L',' || c == L'.' || c == L'!' || c == L'?' || c == L'\0')
        {
            if (inWord)
            {
                buf[bufIdx] = L'\0';

                if (wcscmp(buf, word1) == 0)
                {
                    count1++;
                }
                else if (wcscmp(buf, word2) == 0)
                {
                    count2++;
                }

                inWord = 0;
            }

            if (c == L'\0')
                break;
        }
        else
        {
            if (!inWord)
            {
                if (iswalpha(c))
                {
                    inWord = 1;
                    bufIdx = 0;
                }
            }
            
            if (inWord && bufIdx < 19)
            {
                buf[bufIdx] = c;
                bufIdx++;
            }
        }
    }

    size_t len1 = wcslen(word1);
    size_t len2 = wcslen(word2);

    // длина новой строки + 1 символ для вставки '\0'
    int newStringLength = wcslen(string) + count1 * (len2 - len1) + count2 * (len1 - len2);
    wchar_t* result = (wchar_t*)malloc((newStringLength + 1) * sizeof(wchar_t));

    if (result == NULL)
    {
        wprintf(L"Ошибка выделения памяти\n");
        return;
    }

    // пустая изначально для функции
    result[0] = L'\0';

    // запись в итоговую строку
    buf[0] = L'\0';

    int strIdx = 0; // индекс текущей буквы в итоговой строке
    bufIdx = 0;     // индекс текущей буквы в буфере слова
    inWord = 0;     // флаг если внутри слова

    for (int i = 0; ; i++)
    {
        wchar_t c = string[i];

        if (c == L' ' || c == L'\t' || c == L'\n' || c == L'\r' || c == L',' || c == L'.' || c == L'!' || c == L'?' || c == L'\0')
        {
            if (inWord)
            {
                buf[bufIdx] = L'\0';

                wchar_t* wordToInsert = buf;

                if (wcscmp(buf, word1) == 0)
                {
                    wordToInsert = word2;
                }
                else if (wcscmp(buf, word2) == 0)
                {
                    wordToInsert = word1;
                }

                for (int j = 0; wordToInsert[j] != L'\0'; j++)
                {
                    result[strIdx] = wordToInsert[j];
                    strIdx++;
                }

                inWord = 0;
            }

            result[strIdx] = c;
            strIdx++;

            if (c == L'\0')
                break;
        }
        else
        {
            if (!inWord)
            {
                if (iswalpha(c))
                {
                    inWord = 1;
                    bufIdx = 0;
                }
            }

            if (inWord && bufIdx < 19)
            {
                buf[bufIdx] = c;
                bufIdx++;
            }
            else if (!inWord)
            {
                result[strIdx] = c;
                strIdx++;
            }
        }
    }

    wprintf(L"Результат: %ls\n", result);

    free(result);
    result = NULL;
}

int main()
{
    EnableRu();

    wchar_t command[50] = L"";

    while (1)
    {
        wprintf(L"T1 - Найти сумму элементов массива с нечетными значениями\n");
        wprintf(L"T2 - Найти в каждом нечетном столбце матрицы элемент с максимальным значением\n");
        wprintf(L"T3 - Посчитать количество слов в тексте, начинающихся с согласной буквы\n");
        wprintf(L"T4 - Заменить в тексте L1 на L2, а L2 на L1\n");

        wprintf(L"ex - выход\n");

        wprintf(L"Введите команду: ");
        
        // ввод команды
        if (input(L"%49s", command))
            return;

        wprintf(L"Ввод: %s\n", command);

        // 1 задание
        if (!wcscmp(command, L"T1"))
        {
            MassivInput();
        }
        // 2 задание
        else if (!wcscmp(command, L"T2"))
        {
            MatrixInput();
        }
        // 3 задание
        else if (!wcscmp(command, L"T3"))
        {
            StringWordCount();      // Тестовый текст, каждый отдельный символ разделённый пробелами это слово, всего слов: 15, с гласных 2.
        }
        // 4 задание
        else if (!wcscmp(command, L"T4"))
        {
            StringWordSwitch();     // Кот любит молоко, а пес любит мясо.
        }
        // выход
        else if (!wcscmp(command, L"ex"))
        {
            wprintf(L"Выход\n");
            return 0;
        }
        // неверная команда
        else
        {
            wprintf(L"Неверная команда\n");
        }

        wprintf(L"\n");
        ClearBuffer();
    }

    return 0;
}