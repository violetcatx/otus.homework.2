#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief Структура для удобного хранения и сравнения IP адресов 
 * 
 */
struct IPAddress {
    int byte1;
    int byte2;
    int byte3;
    int byte4;

    /**
     * @brief Перегруженный оператор сравнения
     * 
     * @param other IP адрес для сравнения
     * @return true 
     * @return false 
     */
    bool operator>(const IPAddress& other) const {
        if (byte1 != other.byte1) {
            return byte1 > other.byte1;
        }
        if (byte2 != other.byte2) {
            return byte2 > other.byte2;
        }
        if (byte3 != other.byte3) {
            return byte3 > other.byte3;
        }
        return byte4 > other.byte4;
    }
};

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
        sscanf(line.c_str(), "%d.%d.%d.%d", &ipAddress.byte1, &ipAddress.byte2, &ipAddress.byte3, &ipAddress.byte4);
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
    for (const auto& ipAddress : ipAddresses) {
        std::cout << ipAddress.byte1 << "." << ipAddress.byte2 << "." << ipAddress.byte3 << "." << ipAddress.byte4 << std::endl;
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
                     return (byte1 == -1 || ipAddress.byte1 == byte1) &&
                            (byte2 == -1 || ipAddress.byte2 == byte2);
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
                     return (ipAddress.byte1 == byte) ||
                            (ipAddress.byte2 == byte) ||
                            (ipAddress.byte3 == byte) ||
                            (ipAddress.byte4 == byte);
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
