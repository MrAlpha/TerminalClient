
#ifndef HID_H_
#define HID_H_

void read_led(char ledToRead_parameter);
void read_switch(char switchToRead_parameter);
void set_led(char state, char ledtoChange_parameter);
void help();

#endif /* HID_H_ */