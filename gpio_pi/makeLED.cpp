#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;
#define GPIO "/sys/class/gpio/"
#define FLASH_DELAY 50000

class LED
{
	private: 
		string gpioPath;
		int gpioNumber;
		void writeSysfs(string path, string fname, string value);
	public:
		LED(int gpioNumber);
		virtual void turnOn();
		virtual void turnOff();
		virtual void displayState();
		virtual ~LED();
};

LED::LED(int gpioNumber)
{
	this->gpioNumber = gpioNumber;
	gpioPath = string(GPIO "gpio") + to_string(gpioNumber) + "/";
	cout <<"path "<< gpioPath <<endl;
	writeSysfs(string(GPIO), "export", to_string(gpioNumber));
	usleep(100000);
	writeSysfs(gpioPath, "direction", "out");
}

void LED::writeSysfs(string path, string fname, string value)
{
	ofstream fs;
	fs.open((path+fname).c_str());
	fs << value;
	fs.close();
}

void LED::turnOn()
{
	writeSysfs(gpioPath, "value", "1");
}

void LED::turnOff()
{
	writeSysfs(gpioPath, "value", "0");
}

void LED::displayState()
{
	ifstream fs;
	fs.open((gpioPath + "value").c_str());
	string line;
	cout << "LED state is: ";
	while(getline(fs,line)) cout << line << endl;
	fs.close();
}

LED::~LED()
{
	cout <<"Destroying the LED with GPIO number " << gpioNumber << endl;
	writeSysfs(string(GPIO), "unexport", to_string(gpioNumber));
}

int main(int argc, char* argv[])
{
	LED led(4);
	for (int i = 0; i < 50; i++)
	{
		led.turnOn();
		usleep(FLASH_DELAY);
		led.displayState();
		led.turnOff();
		usleep(FLASH_DELAY);
		led.displayState();
	}
	return 0;
}

