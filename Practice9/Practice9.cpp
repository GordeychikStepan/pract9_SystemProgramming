// Practice9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

int array_size;
int* array;
int target;
int resultIndex = -1;

DWORD WINAPI search_element(LPVOID param) {

    int start = *(int*)param;
    int end = start + array_size / 2;

    for (int i = 0; i < array_size; i++) {

        if (array[i] == target) {
            resultIndex = i;
            break;
        }
    }
    
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    int arr[] = { 12, 24, 37, 49, 54, 62, 74, 85, 92, 103 };
    array = arr;

    array_size = sizeof(arr) / sizeof(arr[0]);
    std::cin >> target;

    HANDLE threads[2]{};
    int startIndex[2] = { 0, array_size / 2 };

    threads[0] = CreateThread(NULL, 0, search_element, &startIndex[0], 0, NULL);
    threads[1] = CreateThread(NULL, 0, search_element, &startIndex[1], 0, NULL);

    WaitForMultipleObjects(2, threads, true, INFINITE);

    if (threads[0] == NULL) 
        return GetLastError();
    if (threads[1] == NULL) 
        return GetLastError();

    CloseHandle(threads[0]);
    CloseHandle(threads[1]);

    if (resultIndex != -1) {
        std::cout << "Элемент " << array[resultIndex] << " найден в позиции: " << resultIndex << std::endl;
    }
    else {
        std::cout << "Элемент " << target << " не найден" << std::endl;
    }
    

    return 0;

    
}

