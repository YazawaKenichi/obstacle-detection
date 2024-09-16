#include <stdio.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/float32.h>
#include <rmw_microros/rmw_microros.h>

#include "pico/stdlib.h"
#include "pico_uart_transports.h"
#include "hardware/adc.h"

#include "functions.h"
#include "obstacle_msgs.h"
#include "main.h"

#define ANALOG_PIN 2
#define LED_PIN 25

#define RESC(X) rescale(X, 4096, 0, 100, -100)

rcl_publisher_t publisher;
Bar bar;

void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    adc_select_input(ANALOG_PIN);
    uint32_t data = adc_read();
    bar.raw.data = data;
    rcl_ret_t ret = rcl_publish(&publisher, &bar.raw, NULL);
}

int main()
{
    rmw_uros_set_custom_transport(
        true,
        NULL,
        pico_serial_transport_open,
        pico_serial_transport_close,
        pico_serial_transport_write,
        pico_serial_transport_read
    );

    adc_init();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    rcl_timer_t timer;
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

    // Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000; 
    const uint8_t attempts = 120;

    bool led = false;

    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);

    if (ret != RCL_RET_OK)
    {
        // Unreachable agent, exiting program.
        return ret;
    }

    rclc_support_init(&support, 0, NULL, &allocator);

    rclc_node_init_default(&node, "obstacle_detecting_bar", "", &support);
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "obstacle_detecting_bar/raw");
    /*
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
        "obstacle_detection/bar/ref");
    */

    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(1),
        timer_callback);

    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_timer(&executor, &timer);

    bar.raw.data = 0;
    while (true)
    {
        led = !led;
        gpio_put(LED_PIN, led);
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    }
    return 0;
}


