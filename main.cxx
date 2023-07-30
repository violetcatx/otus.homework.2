#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <regex>

/**
 * @brief Структура для удобного хранения и сравнения IP адресов 
 * 
 */
struct IPAddress 
{
    std::array<int, 4> content_;    
    
    bool operator>(const IPAddress& other) const 
    {
        for(auto i=0; i < static_cast<int>(this->content_.size()); i++)
        {
            auto ths = this->content_.at(i);
            auto oth = other.content_.at(i);
            if(ths != oth) 
            {
                return ths > oth;
            }
        }
        return false;
    }
};

/**
 * @brief Простенький глуповатый "на скорую руку)" кастомный сплит 
 * 
 */
std::vector<std::string> split(std::string str, char separator) 
{
    std::vector<std::string> strings;
    int startIndex = 0, endIndex = 0;
    for (auto i = 0; i <= static_cast<int>(str.size()); i++) 
    {
        if (str[i] == separator || i == static_cast<int>(str.size())) 
        {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

/**
 * @brief Получение данных из стандартного ввода
 * 
 * @return std::vector<IPAddress> - вектор с прочитанными адресами
 */
std::vector<IPAddress> readIPAddresses() {
    std::vector<IPAddress> ipAddresses;
    std::string line;
    while (std::getline(std::cin, line)) {
        IPAddress ipAddress;
        
        auto fullCounter = 0;
        auto splittedLine = split(line, '.');
        
        for(auto item : splittedLine)
        {
            if(fullCounter < 4)
            {
                try
                {
                    ipAddress.content_[fullCounter] = (std::stoi(item));
                    fullCounter++;
                }
                catch (const std::invalid_argument& ia) 
                {
                    break;
                }
                catch (const std::out_of_range& oor) {
                    break;
                }
                catch (const std::exception& e)
                {
                    break;
                }
            }
        }
        ipAddresses.push_back(ipAddress);
    }
    return ipAddresses;
}

/**
 * @brief Вывод содержимого вектора IP адресов
 * 
 * @param ipAddresses 
 */
void printIPAddresses(const std::vector<IPAddress>& ipAddresses) {
    for (const auto& ipAddress : ipAddresses) 
    {
        auto point = 0;
        for(const auto& byte : ipAddress.content_)
        {
            std::cout << byte;
            if(point < 3)
            {
                std::cout << ".";
            }
            point++;
        }    
        std::cout << std::endl;
    }
}

/**
 * @brief Поиск соответствий первых двух байт заданным и последующее копирование только соответвтвующих IP адресов
 * 
 * @param ipAddresses Вектор IP адресов
 * @param byte1 Эталон первого байта
 * @param byte2 Эталон второго байта
 */
void filterAndPrintIPAddresses(const std::vector<IPAddress>& ipAddresses, int byte1 = -1, int byte2 = -1) {
    std::vector<IPAddress> filteredAddresses;
    std::copy_if(ipAddresses.begin(), ipAddresses.end(), std::back_inserter(filteredAddresses),
                 [byte1, byte2](const IPAddress& ipAddress) {
                    return  (byte1 == -1 || ipAddress.content_[0] == byte1) &&
                            (byte2 == -1 || ipAddress.content_[1] == byte2);
                 });

    printIPAddresses(filteredAddresses);
}

/**
 * @brief Поиск IP адресов, где хотя бы один из байт равен заданному
 * 
 * @param ipAddresses Вектор IP адресов
 * @param byte Эталон хотябы одного любого из байтов
 */
void filterAndPrintIPAddressesAny(const std::vector<IPAddress>& ipAddresses, int byte) {
    std::vector<IPAddress> filteredAddresses;
    std::copy_if(ipAddresses.begin(), ipAddresses.end(), std::back_inserter(filteredAddresses),
                 [byte](const IPAddress& ipAddress) {
                     return (ipAddress.content_[0] == byte) ||
                            (ipAddress.content_[1] == byte) ||
                            (ipAddress.content_[2] == byte) ||
                            (ipAddress.content_[3] == byte);
                 });

    printIPAddresses(filteredAddresses);
}

int main() {
    std::vector<IPAddress> ipAddresses = readIPAddresses();                     //< Читаем адреса из стандартного ввода
    std::sort(ipAddresses.begin(), ipAddresses.end(), std::greater<>());        //< Сортируем в обратном порядке
    printIPAddresses(ipAddresses);                                              //< Выводим результат после сортировки              
    filterAndPrintIPAddresses(ipAddresses, 1);                                  //< Выводим те, у которых первый байт - 1
    filterAndPrintIPAddresses(ipAddresses, 46, 70);                             //< Выводим те, у которых первый байт - 46, а второй - 70
    filterAndPrintIPAddressesAny(ipAddresses, 46);                              //< Выводим те, у которых хотя бы один любой байт 46
    return 0;                                                                   
}
