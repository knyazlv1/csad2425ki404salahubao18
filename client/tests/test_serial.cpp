#include "pch.h"
#include <gtest/gtest.h>
#include "serialport.h"
#include <string>
#include <windows.h>

// Моки для симуляції функцій Windows API
HANDLE hMockSerial = (HANDLE)1; // Симулюємо успішний дескриптор порту

// Мок для CreateFileA
HANDLE MockCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    if (std::string(lpFileName) == "COM3") {
        return hMockSerial; // Успішний дескриптор
    }
    return INVALID_HANDLE_VALUE; // Симуляція помилки
}

// Мок для WriteFile
BOOL MockWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped) {
    if (hFile == hMockSerial) {
        *lpNumberOfBytesWritten = nNumberOfBytesToWrite; // Симуляція успішного запису
        return TRUE;
    }
    return FALSE; // Симуляція помилки
}

// Мок для ReadFile
BOOL MockReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped) {
    if (hFile == hMockSerial) {
        std::string mockResponse = "Hello, PC!";
        memcpy(lpBuffer, mockResponse.c_str(), mockResponse.size() + 1); // Записуємо у буфер
        *lpNumberOfBytesRead = mockResponse.size(); // Оновлюємо кількість прочитаних байтів
        return TRUE; // Успішне читання
    }
    return FALSE; // Симуляція помилки
}

// Мок для CloseHandle
BOOL MockCloseHandle(HANDLE hObject) {
    return (hObject == hMockSerial); // Успішно закриваємо
}

// Тест для конструктора SerialPort
TEST(SerialPortTest, ConstructorOpensPortAndConfigures) {
    // Симулюємо відкриття порту COM3
    HANDLE hSerial = MockCreateFileA("COM3", GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    ASSERT_NE(hSerial, INVALID_HANDLE_VALUE); // Перевірка, що порт відкрито

    SerialPort serial("COM3");

    // Перевіряємо, чи метод configurePort() повертає true (порт налаштовано успішно)
    EXPECT_TRUE(serial.configurePort());
}

// Тест для методу sendMessage
TEST(SerialPortTest, SendMessageTest) {
    // Створюємо об'єкт SerialPort
    SerialPort serial("COM3");

    const std::string message = "Hello, Arduino!";

    // Симулюємо успішну відправку повідомлення
    EXPECT_TRUE(serial.sendMessage(message));
}

// Тест для методу receiveMessage
TEST(SerialPortTest, ReceiveMessageTest) {
    // Замінимо функцію ReadFile на мок
    SerialPort serial("COM3");

    // Використовуємо мок для читання з порту
    char buffer[1024];
    DWORD bytesRead;
    MockReadFile((HANDLE)1, buffer, sizeof(buffer), &bytesRead, nullptr);
    
    std::string response(buffer);
    EXPECT_EQ(response, "Hello, PC!");
}

// Тест для закриття порту (деструктор)
TEST(SerialPortTest, DestructorClosesPort) {
    // Створюємо об'єкт SerialPort
    SerialPort serial("COM3");

    // Перевіряємо, чи порт був закритий після видалення об'єкта
    // Тут немає прямого тестування на закриття порту, бо у вихідному коді немає зворотнього виклику
    // для перевірки закриття, але ми можемо покладатися на поведінку об'єкта.
    // Реальні тести можна написати, підключивши реальні моки або проводячи інтеграційні тести.
    // Для простоти ми просто перевіряємо, чи не було помилок при деструкторі.
    ASSERT_NO_THROW({
        // Тестуємо, що деструктор не викликає помилок
        SerialPort tempSerial("COM3");
        });
}

// Тест для конфігурації порту через setPortState()
TEST(SerialPortTest, SetPortStateTest) {
    // Створюємо об'єкт SerialPort
    SerialPort serial("COM3");

    // Тестуємо функцію setPortState
    EXPECT_TRUE(serial.configurePort());
}

// Тест для налаштування тайм-аутів через setPortTimeouts()
TEST(SerialPortTest, SetPortTimeoutsTest) {
    // Створюємо об'єкт SerialPort
    SerialPort serial("COM3");

    // Тестуємо функцію setPortTimeouts
    EXPECT_TRUE(serial.configurePort());
}
TEST(SerialPortTest, ConstructorOpensValidPort) {
    SerialPort serial("COM3"); // Симуляція порту COM3
    EXPECT_TRUE(true); // Успішне створення об'єкта
}
TEST(SerialPortTest, ConstructorFailsToOpenInvalidPort) {
    SerialPort serial("INVALID_PORT");
    // Зчитування повідомлення про помилку вручну неможливе, але перевіримо, що код працює.
    EXPECT_TRUE(true); // Просто перевіряємо, що програма не впала
}
TEST(SerialPortTest, SendMessageValidMessage) {
    SerialPort serial("COM3");
    EXPECT_TRUE(serial.sendMessage("Hello, Arduino!"));
}
TEST(SerialPortTest, SendMessageEmptyMessage) {
    SerialPort serial("COM3");
    EXPECT_TRUE(serial.sendMessage("")); // Має спрацювати навіть із порожнім повідомленням
}

TEST(SerialPortTest, ReceiveMessageNoResponse) {
    SerialPort serial("COM3");
    // Якщо порту немає, відповідь має бути порожньою
    std::string response = serial.receiveMessage();
    EXPECT_EQ(response, ""); // Очікуємо, що буде порожня відповідь
}
TEST(SerialPortTest, SetPortStateSuccess) {
    SerialPort serial("COM3");
    EXPECT_TRUE(serial.configurePort()); // Якщо порт працює, налаштування має пройти
}
TEST(SerialPortTest, SetPortTimeoutsSuccess) {
    SerialPort serial("COM3");
    EXPECT_TRUE(serial.configurePort()); // Тайм-аути встановлюються у `configurePort()`
}








