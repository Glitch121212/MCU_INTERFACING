typedef enum{
    gpio_port_a,
    gpio_port_b,
    gpio_port_c,
    gpio_port_d
}
GPIO_port_t;

typedef enum{
    gpio_input =0,
    gpio_output
}GPIO_DIR_t;
typedef enum{
    gpio_pin_0,
    gpio_pin_1,
    GPIO_PIN_2,
    gpio_pin_3,
    gpio_pin_4,
    gpio_pin_5,
    gpio_pin_6,
    gpio_pin_7
}GPIO_PIN_t;
typedef enum{
    gpio_low,
    gpio_high
}GPIO_Value_t;

#define GPIO_PORT_INPUT  0x00
#define GPIO_PORT_OUTPUT 0xFF

#define GPIO_PORT_LOW 0x00
#define GPIO_PORT_HIGH 0xFF

void GPIO_VidSetDirection(GPIO_Port_t Port, GPIO_Pin_t Pin , GPIO_VidSetDirection Direction);

