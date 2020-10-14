#include <iostream>

using namespace std;

extern void mainMenu();
extern int subscribe();
extern void connectPublisher();

int main()
{
	int result = 0;

	 result = subscribe();
	if (result != 0) {
		cout << "Subscription failed!" << endl;
		return result;
	}

	connectPublisher();

	mainMenu();
	return result;
}
