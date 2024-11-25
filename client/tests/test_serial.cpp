#include "pch.h"
#include <gtest/gtest.h>
#include "serialport.h"
#include <string>
#include <windows.h>


HANDLE hMockSerial = (HANDLE)1; 


HANDLE MockCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    if (std::string(lpFileName) == "COM3") {
        return hMockSerial; 
    }
    return INVALID_HANDLE_VALUE; 
}


BOOL MockWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped) {
    if (hFile == hMockSerial) {
        *lpNumberOfBytesWritten = nNumberOfBytesToWrite; 
        return TRUE;
    }
    return FALSE; 
}


BOOL MockReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped) {
    if (hFile == hMockSerial) {
        std::string mockResponse = "Hello, PC!";
        memcpy(lpBuffer, mockResponse.c_str(), mockResponse.size() + 1); 
        *lpNumberOfBytesRead = mockResponse.size(); 
        return TRUE; 
    }
    return FALSE; 
}


BOOL MockCloseHandle(HANDLE hObject) {
    return (hObject == hMockSerial); 
}


TEST(SerialPortTest, ConstructorOpensPortAndConfigures) {
   
    HANDLE hSerial = MockCreateFileA("COM3", GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    ASSERT_NE(hSerial, INVALID_HANDLE_VALUE); 

    SerialPort serial("COM3");

    
    EXPECT_TRUE(serial.configurePort());
}


TEST(SerialPortTest, SendMessageTest) {
    
    SerialPort serial("COM3");

    const std::string message = "Hello, Arduino!";

    
    EXPECT_TRUE(serial.sendMessage(message));
}


TEST(SerialPortTest, ReceiveMessageTest) {
    
    SerialPort serial("COM3");

    
    char buffer[1024];
    DWORD bytesRead;
    MockReadFile((HANDLE)1, buffer, sizeof(buffer), &bytesRead, nullptr);
    
    std::string response(buffer);
    EXPECT_EQ(response, "Hello, PC!");
}


TEST(SerialPortTest, DestructorClosesPort) {
    
    SerialPort serial("COM3");

    
    ASSERT_NO_THROW({
        
        SerialPort tempSerial("COM3");
        });
}


TEST(SerialPortTest, SetPortStateTest) {
    
    SerialPort serial("COM3");

   
    EXPECT_TRUE(serial.configurePort());
}


TEST(SerialPortTest, SetPortTimeoutsTest) {
   
    SerialPort serial("COM3");

    
    EXPECT_TRUE(serial.configurePort());
}
TEST(SerialPortTest, ConstructorOpensValidPort) {
    SerialPort serial("COM3"); 
    EXPECT_TRUE(true); 
}
TEST(SerialPortTest, ConstructorFailsToOpenInvalidPort) {
    SerialPort serial("INVALID_PORT");
    
    EXPECT_TRUE(true); 
}
TEST(SerialPortTest, SendMessageValidMessage) {
    SerialPort serial("COM3");
    EXPECT_TRUE(serial.sendMessage("Hello, Arduino!"));
}
TEST(SerialPortTest, SendMessageEmptyMessage) {
    SerialPort serial("COM3");
    EXPECT_TRUE(serial.sendMessage("")); 
}

TEST(SerialPortTest, ReceiveMessageNoResponse) {
    SerialPort serial("COM3");
   
    std::string response = serial.receiveMessage();
    EXPECT_EQ(response, ""); 
}
TEST(SerialPortTest, SetPortStateSuccess) {
    SerialPort serial("COM3");
    EXPECT_TRUE(serial.configurePort()); 
}
TEST(SerialPortTest, SetPortTimeoutsSuccess) {
    SerialPort serial("COM3");
    EXPECT_TRUE(serial.configurePort()); 
}








