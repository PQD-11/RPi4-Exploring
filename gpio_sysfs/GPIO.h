#define GPIO_PATH "/sys/class/gpio/"

namespace exploringRPi {
	enum GPIO_DIRECTION{
		INPUT,
		OUTPUT
	};
	enum GPIO_VALUE{
		LOW = 0,
		HIGH = 1
	};
	enum GPIO_EDGE{
		NONE,
		RISING,
		FALLING,
		BOTH
	};
	
	class GPIO {
		 private:
			int number, debounceTime;
			string name, path;
		 public:
			GPIO(int number);
			virtual int getNumber() {return number;}
			
			virtual int setDirection(GPIO_DIRECTION);
			virtual GPIO_DIRECTION getDirection();
			virtual int setVALUE(GPIO_VALUE);
			virtual GPIO_VALUE getVALUE();
			virtual int toggleOutput();
			virtual int setActiveLow(bool isLow = true);
			virtual int setActiveHigh();
			virtual setDebounceTime(int time) {this->debounceTime = time}
			
			
