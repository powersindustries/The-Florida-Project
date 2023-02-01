#include "String.h"
#include <cstring>
#include <stdio.h>
#include <corecrt_math.h>

#define NULL_TERMINATE_CHAR '\0'

namespace CoreTypes
{


// -------------------------------------------------------
// -------------------------------------------------------
String::String()
    : m_String(nullptr), m_uiStringLength(0)
{
    m_String = new char[1];
    m_String[0] = NULL_TERMINATE_CHAR;
}

// -------------------------------------------------------
// -------------------------------------------------------
String::~String()
{
    if (!m_String)
    {
        delete[] m_String;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
String::String(char* string)
    : m_String(nullptr), m_uiStringLength(0)
{
    if (!string)
    {
        m_String = new char[1];
        m_String[0] = NULL_TERMINATE_CHAR;
        return;
    }

    m_uiStringLength = static_cast<uint32_t>(strlen(string));

    m_String = new char[m_uiStringLength + 1];

    strcpy(m_String, string);
    m_String[m_uiStringLength] = NULL_TERMINATE_CHAR;
}


// -------------------------------------------------------
// -------------------------------------------------------
String::String(const String& string)
    : m_String(nullptr), m_uiStringLength(0)
{
    m_uiStringLength = static_cast<uint32_t>(strlen(string.c_str()));

    m_String = new char[m_uiStringLength + 1];
    strcpy(m_String, string.c_str());

    m_String[m_uiStringLength] = NULL_TERMINATE_CHAR;
}


// -------------------------------------------------------
// -------------------------------------------------------
void String::push_back(char character)
{
    const uint8_t sizeIncrease = 2;
    char* tempString = new char[m_uiStringLength + sizeIncrease];

    for (uint32_t x = 0; x < m_uiStringLength; ++x)
    {
        tempString[x] = m_String[x];
    }

    tempString[m_uiStringLength] = character;
    tempString[m_uiStringLength + 1] = NULL_TERMINATE_CHAR;

    if (!m_String)
    {
        delete[] m_String;
    }
    m_String = tempString;
    m_uiStringLength++;
}


// -------------------------------------------------------
// -------------------------------------------------------
void String::append(const String& string)
{
    const uint8_t sizeIncrease = 1;

    const uint32_t inputStringSize = string.size();
    const uint32_t finalStringSize = m_uiStringLength + inputStringSize;

    char* tempString = new char[finalStringSize + sizeIncrease];

    for (uint32_t x = 0; x < m_uiStringLength; ++x)
    {
        tempString[x] = m_String[x];
    }

    for (uint32_t x = m_uiStringLength; x < finalStringSize; ++x)
    {
        tempString[x] = string.c_str()[x - m_uiStringLength]; // fix later
    }

    tempString[finalStringSize] = NULL_TERMINATE_CHAR;

    if (!m_String)
    {
        delete[] m_String;
    }

    m_String = tempString;
    m_uiStringLength = finalStringSize;
}


// -------------------------------------------------------
// -------------------------------------------------------
void String::append(const char* string)
{
    const uint8_t sizeIncrease = 1;

    const uint32_t inputStringSize = static_cast<uint32_t>(strlen(string));
    const uint32_t finalStringSize = m_uiStringLength + inputStringSize;

    char* tempString = new char[finalStringSize + sizeIncrease];

    for (uint32_t x = 0; x < m_uiStringLength; ++x)
    {
        tempString[x] = m_String[x];
    }

    for (uint32_t x = m_uiStringLength; x < finalStringSize; ++x)
    {
        tempString[x] = string[x - m_uiStringLength];
    }

    tempString[finalStringSize] = NULL_TERMINATE_CHAR;

    if (!m_String)
    {
        delete[] m_String;
    }

    m_String = tempString;
    m_uiStringLength = finalStringSize;
}


// -------------------------------------------------------
// -------------------------------------------------------
void String::append(const uint16_t number)
{
    String numberAsString;
    numberAsString.to_string(number);

    append(numberAsString);
}


// -------------------------------------------------------
// -------------------------------------------------------
void String::to_string(const uint16_t number)
{
    const uint8_t sizeIncrease = 1;
    const uint16_t numberLength = static_cast<int>(((ceil(log10(number)) + 1) * sizeof(char)));

    char* tempString = new char[numberLength + sizeIncrease];
    sprintf(tempString, "%d", number);

    tempString[numberLength] = NULL_TERMINATE_CHAR;

    if (!m_String)
    {
        delete[] m_String;
    }

    m_String = tempString;
    m_uiStringLength = numberLength;

}


// -------------------------------------------------------
// -------------------------------------------------------
String& String::operator=(const String& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    m_uiStringLength = static_cast<uint32_t>(strlen(rhs.c_str()));

    if (!m_String)
    {
        delete[] m_String;
    }

    m_String = new char[m_uiStringLength + 1];
    strcpy(m_String, rhs.c_str());

    return *this;
}


// -------------------------------------------------------
// -------------------------------------------------------
String& String::operator=(const char* rhs)
{
    if (this->m_String == rhs)
    {
        return *this;
    }

    m_uiStringLength = static_cast<uint32_t>(strlen(rhs));

    if (!m_String)
    {
        delete[] m_String;
    }

    m_String = new char[m_uiStringLength + 1];
    strcpy(m_String, rhs);

    return *this;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool String::operator<(const String& rhs) const
{
    return strcmp(this->m_String, rhs.c_str()) > 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool String::operator<(const char* rhs) const
{
    return strcmp(this->m_String, rhs) > 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool String::operator>(const String& rhs) const
{
    return strcmp(this->m_String, rhs.c_str()) < 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool String::operator>(const char* rhs) const
{
    return strcmp(this->m_String, rhs) < 0;

}


// -------------------------------------------------------
// -------------------------------------------------------
char& String::operator[](size_t index)
{
    return m_String[index];
}

}

