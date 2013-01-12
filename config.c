	
	
	
	void config()
	{
		/************************************************************************/
		/* USART konfigurieren                                                  */
		/************************************************************************/
	
		UCSRB = (1<<RXEN) | (1<<TXEN);        //USART Receiver und Transmitter einschalten
																					//die n�tigen Ausgangspins des Controllers werden
																					//automatisch auf USART-Funktionalit�t umgeschalten
	
		UCSRC = (1<<URSEL)|(3<<UCSZ0);    				//Asynchron, keine Parit�t, 1 Stoppbit, 8 Datenbits
																							//URSEL muss f�r Zugriff auf UCSRC gesetzt sein
	
		UBRRH = 0;										//Einstellen der Baudrate (9600)
		UBRRL = 51;										//Werte aus der Tabelle im Datenblatt
	
		/************************************************************************/
		/* Timer 1 konfigurieren    (generiert Takt zum Ausl�sen d. Trap Fkt.   */
		/************************************************************************/

		TCCR1B  = (1<<CS12) | (1<<CS10); // Prescaler: 1056
		// Timer Overflow Interrupt wird NICHT freigeschaltet. ->Wird bei einschalten der Trap Funktion ausgef�hrt
	
		/************************************************************************/
		/* Timer 2 konfigurieren    (generiert blink Takt f�r LEDs)             */
		/************************************************************************/
	
		TCCR2  = (1<<CS22) | (1<<CS20); // Prescaler: 1056
		TIMSK |= (1<<TOIE2);            // Timer Overflow Interrupt freischalten
	

		/************************************************************************/
		/* PORT A f�r LEDs:                                                     */
		/************************************************************************/

		DDRA = 0xff;							//Port A als Ausgang Definieren (f�r die LEDs)
		PORTA = 0xff;							//Alle Pins an Port A auf 1 setzen -> LEDs sind low activ;

		/************************************************************************/
		/* PORT B f�r Taster:                                                   */
		/************************************************************************/
		DDRB= 0x00;							//Port B als Eingang (f�r Taster)
		PORTB= 0xff;						//Pull-ups on
		
		/************************************************************************/
		/* Globale Interrupts einschalten                                       */
		/************************************************************************/
		sei();
	}	