#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0 	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN 	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS 	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0 ""
#define PIN 0
#define FLAGS 0
#endif

#define SLEEP_TIME 1000

void main(void)
{	
	const struct device *dev;
	bool led_on = true;
	int ret;

	dev = device_get_binding(LED0);
	if (dev == NULL) {
		printf("\nError binding GPIO device\n");
		return;
	}

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		printf("\nError configuring GPIO\n");
		return;
	}

	while(true) {
		gpio_pin_set(dev, PIN, (int)led_on);
		led_on = !led_on;
		k_msleep(SLEEP_TIME);
	}
}