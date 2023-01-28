
#ifndef GPIO_H_
#define GPIO_H_
#include<string>
#include<fstream>
using std::string;
using std::ofstream;

#define GPIO_PATH "/sys/class/gpio/"

namespace exploringRPi {

typedef int (*CallbackType)(int);
enum GPIO_DIRECTION{ INPUT, OUTPUT };
enum GPIO_VALUE{ LOW=0, HIGH=1 };
enum GPIO_EDGE{ NONE, RISING, FALLING, BOTH };

class GPIO {
private:
	int number, debounceTime;
	string name, path;
public:
	GPIO(int number);                     
	virtual int getNumber() { return number; }

	virtual int  setDirection(GPIO_DIRECTION);
	virtual GPIO_DIRECTION getDirection();
	virtual int  setValue(GPIO_VALUE);
	virtual int  toggleOutput();
	virtual GPIO_VALUE getValue();
	virtual int  setActiveLow(bool isLow=true);  
	virtual int  setActiveHigh();                
	virtual void setDebounceTime(int time) { this->debounceTime = time; }

	virtual int  streamOpen();
	virtual int  streamWrite(GPIO_VALUE);
	virtual int  streamClose();
	virtual int  toggleOutput(int time); 
	virtual int  toggleOutput(int numberOfTimes, int time);
	virtual void changeToggleTime(int time) { this->togglePeriod = time; }
	virtual void toggleCancel() { this->threadRunning = false; }

	virtual int  setEdgeType(GPIO_EDGE);
	virtual GPIO_EDGE getEdgeType();
	virtual int  waitForEdge();        
	virtual int  waitForEdge(CallbackType callback); 
	virtual void waitForEdgeCancel() { this->threadRunning = false; }

	virtual ~GPIO();  
private:
	int write(string path, string filename, string value);
	int write(string path, string filename, int value);
	string read(string path, string filename);
	int exportGPIO();
	int unexportGPIO();
	ofstream stream;
	pthread_t thread;
	CallbackType callbackFunction;
	bool threadRunning;
	int togglePeriod;  
	int toggleNumber;  
	friend void* threadedPoll(void *value);
	friend void* threadedToggle(void *value);
};

void* threadedPoll(void *value);      
void* threadedToggle(void *value);  

}

#endif /* GPIO_H_ */
