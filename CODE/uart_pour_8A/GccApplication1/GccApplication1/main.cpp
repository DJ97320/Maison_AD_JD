#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL
#define BAUD_RATE 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

void USART_Init() {
	// Configurer le taux de transmission
	//UBRRH = (uint8_t)(UBRR_VALUE >> 8);
	UBRRL = (uint8_t)UBRR_VALUE;

	// Activer l'émetteur et le récepteur UART
	UCSRB = (1 << TXEN) | (1 << RXEN);

	// Configurer le format de trame: 8 bits de données, 1 bit de stop
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void USART_Transmit(uint8_t data) {
	// Attendre que le tampon de transmission soit vide
	while (!(UCSRA & (1 << UDRE)))
	;

	// Charger les données dans le tampon de transmission
	UDR = data;
}

uint8_t USART_Receive() {
	// Attendre que les données soient disponibles dans le tampon de réception
	while (!(UCSRA & (1 << RXC)))
	;

	// Retourner les données reçues
	return UDR;
}

int main() {
	// Initialiser la communication UART
	USART_Init();

	while (1) {
		// Envoyer "Hello, World!" via UART
		USART_Transmit('H');
		USART_Transmit('e');
		USART_Transmit('l');
		USART_Transmit('l');
		USART_Transmit('o');
		USART_Transmit(',');
		USART_Transmit(' ');
		USART_Transmit('W');
		USART_Transmit('o');
		USART_Transmit('r');
		USART_Transmit('l');
		USART_Transmit('d');
		USART_Transmit('!');
		USART_Transmit('\n');

		// Attendre un peu avant de répéter
		_delay_ms(1000);
	}

	return 0;
}
