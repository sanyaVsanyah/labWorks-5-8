#include <iostream>
#include <string>
#include <stdexcept>

struct WordIndices {
    size_t start;
    size_t end;
};

void EnterStr(std::string&);
void OutputStr(const std::string&);
std::string CheckString(std::string&, const std::string&);
std::string TransformString(std::string&, const WordIndices*, int);  // Убрали const
bool IsDigitsOnly(const std::string&, size_t, size_t);

int main()
{
    std::string myStr;
    std::string delimiters = " !@#$%^&*()";
    try
    {
        
        EnterStr(myStr);
        if (myStr.length() == 0)
        {
            throw std::logic_error("Wrong size of your string");
        }

        std::cout << "Original string: ";
        OutputStr(myStr);
        std::string transformedStr = CheckString(myStr, delimiters);
        std::cout << "Transformed string: ";
        OutputStr(transformedStr);
    }
    catch (std::logic_error& error)
    {
        std::cout << error.what();
    }
    return 0;
}

void EnterStr(std::string& myStr)
{
    std::getline(std::cin, myStr);
}

void OutputStr(const std::string& myStr)
{
    std::cout << myStr << '\n';
}

bool IsDigitsOnly(const std::string& str, size_t start, size_t end)
{
    for (size_t i = start; i <= end; ++i)
    {
        char c = str[i];
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    return true;
}

std::string TransformString(std::string& myStr, const WordIndices* words, int wordCount)
{
    std::string result;
    size_t currentPos = 0;

    for (int i = 0; i < wordCount; ++i)
    {
        result += myStr.substr(currentPos, words[i].start - currentPos);

        size_t wordLength = words[i].end - words[i].start + 1;
        std::string word = myStr.substr(words[i].start, wordLength);

        if (wordLength < 5 && IsDigitsOnly(myStr, words[i].start, words[i].end))
        {
            word = std::string(5 - wordLength, '0') + word;
        }

        result += word;
        currentPos = words[i].end + 1;
    }

    result += myStr.substr(currentPos);

    return result;
}

std::string CheckString(std::string& myStr, const std::string& delimiters)
{
    size_t pos1 = 0, pos2 = 0;
    int wordCount = 0;
    pos1 = 0;
    while ((pos1 = myStr.find_first_not_of(delimiters, pos1)) != std::string::npos)
    {
        ++wordCount;
        pos1 = myStr.find_first_of(delimiters, pos1);
        if (pos1 == std::string::npos)
        {
            break;
        }
        pos1++;
    }
    WordIndices* words = new WordIndices[wordCount];
    pos1 = 0;
    int index = 0;
    while ((pos1 = myStr.find_first_not_of(delimiters, pos1)) != std::string::npos)
    {
        pos2 = myStr.find_first_of(delimiters, pos1);
        words[index].start = pos1;
        if (pos2 == std::string::npos)
        {
            words[index].end = myStr.length() - 1;
            pos1 = myStr.length();
        }
        else
        {
            words[index].end = pos2 - 1;
            pos1 = pos2 + 1;
        }
        ++index;
    }

    std::string result = TransformString(myStr, words, wordCount);

    delete[] words;
    return result;
}