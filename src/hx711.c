
void hx711_init()
{
    pinMode(PIN_SLK, OUTPUT);
    pinMode(PIN_OUT, INPUT);
}

void hx711_reset()
{
}

///// !不完全! /////
long AE_HX711_Read()
{
    long data = 0;
    while(/* GPIO Read */(PIN_OUT) != 0)
    {
    }
    /* 10 ms 待つ */
    for(int i = 0; i < 24; i++)
    {
        /* GPIO Write */(PIN_SLK, 1);
        /* 5 ms 待つ */
        /* GPIO Write */(PIN_SLK, 0);
        /* 5 ms 待つ */
        data = ( data << 1 ) | ( /* GPIO Read */(PIN_OUT));
    }
    /* GPIO Write */(PIN_SLK, 1);
    /* 10 ms */
    /* GPIO Write */(PIN_SLK, 0);
    /* 10 ms */
    return data ^ 0x800000;
}

long AE_HX711_Averaging(long adc, char num)
{
    long sum = 0;
    for(int i = 0; i < num; i++)
    {
        sum += AE_HX711_Read();
        return sum / num;
    }
}

float AE_HX711_getGram(char num)
{
    data = AE_HX711_Averaging(AE_HX711_Read(), num) * HX711_ADC1bit;
}



