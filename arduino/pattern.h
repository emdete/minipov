#define countof(x) (sizeof(x) / sizeof(*(x)))


uint8_t ee_text[10][20] EEMEM;

class Pattern : public Command {
	uint8_t ee_index = 0;
protected:
	void write_pattern(const char* text) {
		serial->println();
		while (*text) {
			for (int i=0;i<font_width;i++) {
				const uint8_t * p = font_pattern(*text, i);
				uint8_t pattern = p?pgm_read_byte(p):0;
				for (int j=0;j<8;j++) {
					if (pattern & (1<<(7-j))) {
						serial->print('X');
					}
					else {
						serial->print(' ');
					}
				}
				serial->println();
			}
			text++;
			serial->println();
		}
	}
public:
	virtual int execute(const char* command) {
		if (*command == 'r' && command[1] == 0) {
			char text[sizeof(ee_text[0])];
			eeprom_read_block(text, (void*)ee_text[ee_index], sizeof(text));
			write_pattern(text);
			return 0;
		}
		else if (*command == 'w' && command[1] == ' ') {
			// (command+2)[sizeof(ee_text[0])-1] = 0;
			eeprom_update_block (command+2, (void*)ee_text[ee_index], sizeof(ee_text[0]));
			write_pattern(command+2);
			return 0;
		}
		else if (*command == 'i' && command[1] == 0) {
			ee_index = (ee_index+1) % countof(ee_text);
			serial->print("index "); serial->println(ee_index);
			return 0;
		}
		else if (*command == 'd' && command[1] == 0) {
			ee_index = (ee_index+countof(ee_text)-1) % countof(ee_text);
			serial->print("index "); serial->println(ee_index);
			return 0;
		}
		else if (*command == 'p' && command[1] == 0) {
			serial->print("counter index "); serial->println(counter_index);
			return 0;
		}
		return 1;
	}
};
