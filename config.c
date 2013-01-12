	
	
	
	void config()
	{
		/************************************************************************/
		/* USART konfigurieren                                                  */
		/************************************************************************/
	
		UCSRB = (1<<RXEN) | (1<<TXEN);        //USART Receiver und Transmitter einschalten
																					//die nötigen Ausgangspins des Controllers werden
																					//automatisch auf USART-Funktionalität umgeschalten
	
		UCSRC = (1<<URSEL)|(3<<UCSZ0);    				//Asynchron, keine Parität, 1 Stoppbit, 8 Datenbits
																							//URSEL muss für Zugriff auf UCSRC gesetzt sein
	
		UBRRH = 0;										//Einstellen der Baudrate (9600)
		UBRRL = 51;										//Werte aus der Tabelle im Datenblatt
	
		/************************************************************************/
		/* Timer 1 konfigurieren    (generiert Takt zum Auslösen d. Trap Fkt.   */
		/************************************************************************/

		TCCR1B  = (1<<CS12) | (1<<CS10); // Prescaler: 1056
		// Timer Overflow Interrupt wird NICHT freigeschaltet. ->Wird bei einschalten der Trap Funktion ausgeführt
	
		/************************************************************************/
		/* Timer 2 konfigurieren    (generiert blink Takt für LEDs)             */
		/************************************************************************/
	
		TCCR2  = (1<<CS22) | (1<<CS20); // Prescaler: 1056
		TIMSK |= (1<<TOIE2);            // Timer Overflow Interrupt freischalten
	

		/************************************************************************/
		/* PORT A für LEDs:                                                     */
		/************************************************************************/

		DDRA = 0xff;							//Port A als Ausgang Definieren (für die LEDs)
		PORTA = 0xff;							//Alle Pins an Port A auf 1 setzen -> LEDs sind low activ;

		/************************************************************************/
		/* PORT B für Taster:                                                   */
		/************************************************************************/
		DDRB= 0x00;							//Port B als Eingang (für Taster)
		PORTB= 0xff;						//Pull-ups on
		
		/************************************************************************/
		/* Globale Interrupts einschalten                                       */
		/************************************************************************/
		sei();
	}	