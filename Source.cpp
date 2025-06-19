#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

void NewStr(char*&);
void DeleteStr(char*&);
void PolindromeStr(char*);
bool isPalindrome(const char*);
void bubbleSortByLength(char* words[], int count);
int compareByLength(const char* a, const char* b);

int main()
{
    try {
        char* str = nullptr;
        NewStr(str);
        if (strlen(str) == 0)
        {
            throw std::logic_error("Empty str.");
        }
        std::cout << "Your str: " << str << std::endl;
            PolindromeStr(str);
            DeleteStr(str);
    }
    catch (std::logic_error e)
    {
        std::cout << e.what();
    }
    return 0;
}

void NewStr(char*& str)
{
    str = new char[255];
    std::cout << "Enter str: ";
    std::cin.getline(str, 255);
}

void DeleteStr(char*& str)
{
    delete[] str;
    str = nullptr;
}

int compareByLength(const char* a, const char* b) 
{
    return strlen(a) - strlen(b);
}

void bubbleSortByLength(char* words[], int count)
{
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j) 
        {
            if (compareByLength(words[j], words[j + 1]) > 0)
            {
                char* temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

void PolindromeStr(char* str)
{
    const int MAX_WORDS = 100;
    char* palindromes[MAX_WORDS];
    int count = 0;

    char* str_copy = new char[strlen(str) + 1];
    strcpy(str_copy, str);

    char* token = strtok(str_copy, " ");
    while (token != nullptr && count < MAX_WORDS) 
    {
        if (isPalindrome(token))
        {
            palindromes[count] = new char[strlen(token) + 1];
            strcpy(palindromes[count], token);
            count++;
        }
        token = strtok(nullptr, " ");
    }

    bubbleSortByLength(palindromes, count);

    int total_length = 0;
    for (int i = 0; i < count; ++i) 
    {
        total_length += strlen(palindromes[i]) + 1;
    }

    char* result = new char[total_length + 1];
    result[0] = '\0';

    for (int i = 0; i < count; ++i)
    {
        strcat(result, palindromes[i]);
        if (i != count - 1) 
        {
            strcat(result, " ");
        }
    }

    std::cout << "Sorted palindromes: " << result << std::endl;
    delete[] str_copy;
    for (int i = 0; i < count; ++i) 
    {
        delete[] palindromes[i];
    }
    delete[] result;
}

bool isPalindrome(const char* word)
{
    int len = strlen(word);
    int left = 0;
    int right = len - 1;
    while (left < right)
    {
        if (word[left] != word[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}