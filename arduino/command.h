class Command {
protected:
	Stream* serial;
	char command[32];
	int index = 0;
public:
	Command() {
		command[index] = 0;
	}
	void setSerial(HardwareSerial* serial) {
		serial->begin(115200);
		this->serial = serial;
		this->serial->println();
#		ifdef HAVE_HWSERIAL0
			this->serial->println(F("Has hardware serial 0"));
#			ifdef HAVE_HWSERIAL1
				this->serial->println(F("Has hardware serial 1"));
#			endif
#		endif
		this->serial->println(BOARD_TYPE);
		this->serial->print(F("CPU Frequency = ")); this->serial->print(F_CPU / 1000000); this->serial->println(F(" MHz"));
		this->serial->print(F("Has ")); this->serial->print(E2END+1); this->serial->println(F(" bytes of eeprom"));
		this->serial->print(TIMER_INTERRUPT_VERSION); this->serial->println(TIMER_INTERRUPT_GENERIC_VERSION);
		this->serial->println(F("OK"));
		this->serial->print(F("> "));
		this->serial->flush();
	}
	void process() {
		char c = serial->read();
		//this->serial->print('['); this->serial->print((int)c); this->serial->print(']');
		if (c >= 32) {
			if (index<(int)sizeof(command)-2) {
				command[index++] = c;
			}
			serial->print(c);
			serial->flush();
		}
		else if (c == 10) {
			this->serial->println();
			command[index] = 0;
			//this->serial->println(); this->serial->print("Command is "); this->serial->println(command);
			if (!execute(command)) {
				this->serial->println(F("OK"));
			}
			else {
				this->serial->println(F("ERROR"));
			}
			index = 0;
			this->serial->print(F("> "));
			this->serial->flush();
		}
	}
	virtual int execute(const char* command);
	int available(void) {
		return this->serial->available();
	}
};

