## Power consumption

In order to reduce the power consumption the device is put in sleep mode after 100 s of inactivity.

Here are some tests using v1.6.1.

Board consumption awake: 10mA

### Sleep mode: 1.10mA

```
cli();
sleep_enable();
sei();
sleep_cpu();
sleep_disable();
```

### Sleep mode, no ADC: 1.03mA

Turning off ADC allows to win around 0.07A

```
ADCSRA &= ~(1 << ADEN); // Disable ADC

cli();
sleep_enable();
sei();
sleep_cpu();
sleep_disable();

ADCSRA |= (1 << ADEN); // enable A/D
```
