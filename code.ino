void send_Din(char, unsigned char);
void cs_high_low();
void enable();
void init();
void out_din(char);
void out_clk(char);
void out_cs(char);

#define shut_down 0x0C
#define brightness 0x0A
#define scan_limit 0x0B
#define decode_mode 0x09

char led_data1[8] = {0xFE, 0x80, 0x80, 0xFE, 0x80, 0x80, 0x80, 0xFE}; //'E'
char led_data2[8] = {0xFE, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFE}; //'C'
char led_data3[8] = {0xFE, 0x80, 0x80, 0xFE, 0x80, 0x80, 0x80, 0xFE}; //'E'
char led_data4[8] = {0x81, 0xC1, 0xA1, 0x91, 0x89, 0x85, 0x83, 0x81}; //'N'
void setup()
{
    init();
    out_cs(0x00);

    send_Din(scan_limit, 0x07);
    send_Din(scan_limit, 0x07);
    send_Din(scan_limit, 0x07);
    send_Din(scan_limit, 0x07);
    cs_high_low();

    send_Din(decode_mode, 0x00);
    send_Din(decode_mode, 0x00);
    send_Din(decode_mode, 0x00);
    send_Din(decode_mode, 0x00);
    cs_high_low();

    send_Din(brightness, 0x01);
    send_Din(brightness, 0x01);
    send_Din(brightness, 0x01);
    send_Din(brightness, 0x01);
    cs_high_low();

    send_Din(shut_down, 0x01);
    send_Din(shut_down, 0x01);
    send_Din(shut_down, 0x01);
    send_Din(shut_down, 0x01);
    cs_high_low();

    while (1)
    {
        for (char i = 1; i < 9; i++)
        {
            send_Din(i, led_data1[i - 1]);
            send_Din(i, led_data2[i - 1]);
            send_Din(i, led_data3[i - 1]);
            send_Din(i, led_data4[i - 1]);
            cs_high_low();
        }
    }
}

void send_Din(char addr, unsigned char data)
{
    for (char i = 7; i >= 0; i--)
    {
        out_din((addr >> i) & 0x01);
        enable();
    }

    for (char i = 7; i >= 0; i--)
    {
        out_din((data >> i) & 0x01);
        enable();
    }
}

void cs_high_low()
{
    out_cs(0x01);
    delay1();
    out_cs(0x00);
}

void enable()
{
    out_clk(0x01);
    delay1();
    out_clk(0x00);
    delay1();
}

void init()
{
    char *ddr_din = (char *)0x30;
    *ddr_din = 0x01;

    char *ddr_clk = (char *)0x107;
    *ddr_clk = 0x01;

    char *ddr_cs = (char *)0x10A;
    *ddr_cs = 0x01;
}

void out_din(char data)
{
    char *out = (char *)0x31;
    *out = data;
}

void out_clk(char data)
{
    char *out = (char *)0x108;
    *out = data;
}

void out_cs(char data)
{
    char *out = (char *)0x10B;
    *out = data;
}

void delay1()
{
    volatile long i;
    for (i = 0; i < 100; i++)
        ;
}

void loop()
{
    // put your main code here, to run repeatedly:
}
