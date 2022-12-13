from time import sleep
import erpc
from remote_control import *
import sys

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("Usage: python led_test_client.py <serial port to use>")
        exit()

    # Initialize all erpc infrastructure
    xport = erpc.transport.SerialTransport(sys.argv[1], 9600)
    client_mgr = erpc.client.ClientManager(xport, erpc.basic_codec.BasicCodec)
    client = client.remote_controlClient(client_mgr)

    print("Initialing")
    client.remote_locate(0, 0)
    print("Finish Initialize")
    while True:
        n = input()
        if n[0] == 'p':
            for i in n[2:]:
                client.remote_putc(ord(i))
        elif n[0] == 'l':
            n = n.split(' ')
            client.remote_locate(int(n[1]), int(n[2]))
        elif n == 'end':
            break
