#include "mbed.h"
#include "drivers/DigitalOut.h"

#include "erpc_simple_server.h"
#include "erpc_basic_codec.h"
#include "erpc_crc16.h"
#include "UARTTransport.h"
#include "DynamicMessageBufferFactory.h"
#include "remote_control_server.h"

#include "TextLCD.h"
/**
 * Macros for setting console flow control.
 */
#define CONSOLE_FLOWCONTROL_RTS 1
#define CONSOLE_FLOWCONTROL_CTS 2
#define CONSOLE_FLOWCONTROL_RTSCTS 3
#define mbed_console_concat_(x) CONSOLE_FLOWCONTROL_##x
#define mbed_console_concat(x) mbed_console_concat_(x)
#define CONSOLE_FLOWCONTROL mbed_console_concat(MBED_CONF_TARGET_CONSOLE_UART_FLOW_CONTROL)

static BufferedSerial pc(USBTX, USBRX); // tx, rx
I2C i2c_lcd(D14, D15);
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2); 
/****** erpc declarations *******/

int remote_putc(int c)
{
    printf("Recieve p! %d\n", c);
    char temp = c;
    lcd.putc(temp);
    return 0;
}

void remote_locate(int column, int row)
{
    printf("Recieve l! %d %d\n", column, row);
    lcd.locate(column, row);
}
/** erpc infrastructure */
ep::UARTTransport uart_transport(D1, D0, 9600);
ep::DynamicMessageBufferFactory dynamic_mbf;
erpc::BasicCodecFactory basic_cf;
erpc::Crc16 crc16;
erpc::SimpleServer rpc_server;

/** LED service */
remote_control_service led_service;

int main(void)
{

    // Initialize the rpc server
    uart_transport.setCrc16(&crc16);

    // Set up hardware flow control, if needed
#if CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_RTS
    uart_transport.set_flow_control(mbed::SerialBase::RTS, STDIO_UART_RTS, NC);
#elif CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_CTS
    uart_transport.set_flow_control(mbed::SerialBase::CTS, NC, STDIO_UART_CTS);
#elif CONSOLE_FLOWCONTROL == CONSOLE_FLOWCONTROL_RTSCTS
    uart_transport.set_flow_control(mbed::SerialBase::RTSCTS, STDIO_UART_RTS, STDIO_UART_CTS);
#endif

    printf("Initializing server.\n");
    rpc_server.setTransport(&uart_transport);
    rpc_server.setCodecFactory(&basic_cf);
    rpc_server.setMessageBufferFactory(&dynamic_mbf);

    // Add the led service to the server
    printf("Adding LED server.\n");
    rpc_server.addService(&led_service);

    // Run the server. This should never exit
    printf("Running server.\n");
    rpc_server.run();
}