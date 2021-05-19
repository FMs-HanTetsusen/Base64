#include <iostream>
#include <string>
#include <algorithm>
#include "base64.hpp"

char base_2_char(unsigned int); // convert Base64 sextet number to char
unsigned int char_2_base(char); // convert Base64 char to sextet number
void encode(std::string);
void decode(std::string);

int main(int argc, char const *argv[])
{
    std::string command, input;

    while (true)
    {
        std::cout << "Choose 'enc' for encoding, 'dec' for decoding, 'exit' to exit: ";
        std::getline(std::cin, command); // use std::getline() to avoid '\n' or '\r\n' left in istream

        if (command.compare("enc") == 0)
        {
            std::cout << std::endl << "Raw text input:" << std::endl << std::endl;
            std::getline(std::cin, input);
            std::cout << std::endl << "Encoded output:" << std::endl << std::endl;
            encode(input);
        }
        else if (command.compare("dec") == 0)
        {
            std::cout << std::endl << "Base64 code input:" << std::endl << std:: endl;
            std::getline(std::cin, input);
            std::cout << std::endl << "Decoded output:" << std::endl << std::endl;
            decode(input);
        }
        else if (command.compare("exit") == 0)
        {
            break;
        }
    }
    
    return 0;
}

char base_2_char(unsigned int i)
{
    if (i >= 0 && i <= 25) return (i + 65); 
    else if (i >= 26 && i <= 51) return (i + 71);
    else if (i >= 52 && i <=61) return (i - 4);
    else if (i == 62) return (i - 19);
    else return (i - 16);
}

unsigned int char_2_base(char c)
{
    if (c >= 'A' && c <= 'Z') return (c - 65);
    else if (c >= 'a' && c <= 'z') return (c - 71);
    else if (c >= '0' && c <= '9') return (c + 4);
    else if (c == '+') return (c + 19);
    else return (c + 16);
}

void encode(std::string input)
{
    int str_len = input.length();
    int pad = 3 - str_len % 3;
    
    if (pad != 3) input.append(pad, '\0');

    union base64 data;
    std::string output;

    for (int i = 0; i < str_len; i += 3)
    {
        data.ascii.a = (unsigned int) input.at(i);
        data.ascii.b = (unsigned int) input.at(i + 1);
        data.ascii.c = (unsigned int) input.at(i + 2);

        output.append(1, base_2_char(data.base64.a));
        output.append(1, base_2_char(data.base64.b));
        output.append(1, base_2_char(data.base64.c));
        output.append(1, base_2_char(data.base64.d));
    }

    if (pad != 3) output.replace(output.end() - pad, output.end(), pad, '=');

    std::cout << output << std::endl << std::endl;
}

void decode(std::string input)
{
    int str_len = input.length();
    int pad = count(input.begin(), input.end(), '=');

    input.replace(input.end() - pad, input.end(), pad, 'A');
    
    union base64 data;
    std::string output;

    for (int i = 0; i < str_len; i += 4)
    {
        data.base64.a = char_2_base(input.at(i));
        data.base64.b = char_2_base(input.at(i + 1));
        data.base64.c = char_2_base(input.at(i + 2));
        data.base64.d = char_2_base(input.at(i + 3));

        output.append(1, data.ascii.a);
        output.append(1, data.ascii.b);
        output.append(1, data.ascii.c);
    }

    output.erase(output.end() - pad, output.end());

    std::cout << output << std::endl << std::endl;
}