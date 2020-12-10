#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

void f1();
void f2();

LONG a[15];

int main() {
	for (int i = 0; i < 15; i++) a[i] = 0;
	HANDLE thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)f1, NULL, 0, 0);
	if (thread1 == NULL) return GetLastError();
	HANDLE thread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)f2, NULL, 0, 0);
	if (thread2 == NULL) return GetLastError();
	cin.get();
	TerminateThread(thread1, 0);
	CloseHandle(thread1);
	TerminateThread(thread2, 0);
	CloseHandle(thread2);
	return 0;
}

void f1() {
	cout << "Thread 1 started" << endl;
	srand(time_t(NULL));
	while (true)
	{
		cout << "t1: ";
		for (int i = 0; i < 15; i++) {
			long k = rand() * 300 / (RAND_MAX)-150;
			InterlockedExchangeAdd(&a[i], k);
			cout << a[i] << " ";
		}
		cout << endl;
		Sleep(2000);
	}
	return;
}

void f2() {
	Sleep(1000);
	cout << "Thread 2 started" << endl;
	srand(time_t(NULL));
	while (true)
	{
		cout << "t2: ";
		for (int i = 0; i < 15; i++) {
			if (abs(a[i]) % 2 == 0) {
				a[i] = 0;
			}
			cout << a[i] << " ";
		}
		cout << endl << endl;
		Sleep(2000);
	}
	return;
}