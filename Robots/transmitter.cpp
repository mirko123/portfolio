/*Това е програмата, която се намира върху ардуиното и служи за дистанционно управление на робота. Има 2 потенциометъра, RF приемник от 315 MHz и предавател на 434 MHz Посредством RF предавателя изпращам информация за управлението на робота.
*/
int pot1=0, pot2=0; //Това са стойностите на потенциометрите,
#include <VirtualWire.h> //Този клас е нужен за приемника и предавателя.
void setup()
{
    Serial.begin(9600);	  // Debugging only
}

void loop()
{
    //Тук се четат стойностите на потенциометрите. Те биват от 0 до 1024.
    pot1=analogRead(0); 
    pot2=analogRead(1);
    send('a',pot1);
    send('b',pot2);
}

/*С функцията send се изпраща информация от приемника към предавателя. Тя предава стойностите на потенциометрите.
*/
void send(char promenliva, int stoinost)
{
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    int n=broi(stoinost); /*Тази променлива приема от колко цифри се състои стойността на потенциометъра.*/
    char str2[n]; /*Създаваме масив от char елементи с дължина с 1, по-голяма от броят на цифрите в стойността на потенциометъра.*/
    memset (str2, 0, sizeof(str2));
    snprintf(str2, n+1, "%d", stoinost); //Като използвам snprintf(), превръщам int в char.
    str2[n]=promenliva; /*Като последен знак от масива задавам за кого от двата потенциометъра се отнася дадената стойност, 'a' или 'b'.*/
    const char *msg = str2; //Не може да се изпраща обикновен char масив, заради което е нуждно това.
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
}

/*С тази функция се намира броя на цифрите в едно число, като се проверява колко пъти то може да се раздели на 10.
*/
int broi(int number)
{
    int n=0;
    while(number>0)
    {
      number=number/10;
      n++;
    }
    return n;
}

//С тази функция чете приемника.
void read()
{    
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	for (int i = 0; i < buflen; i++)
	{
	    Serial.write(buf[i]);
	    Serial.println(" ");
	}
    }
}
