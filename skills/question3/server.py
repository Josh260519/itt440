# Defining host and port to listen for connections
host = '192.168.17.128'  # IP Address of host
port = 8484  # Port to listen to

def bar_to_atm(pressure):
    return pressure / 1.013
    

def handle_client(client_socket, client_address):
    # Receive data from the client
    while True:
        data = client_socket.recv(1024).decode('utf-8')
        if not data:
            break
        print("Received data from {}: {}: {}".format(client_address[0], client_address[1], data))

    # Close the client socket
    client_socket.close()
    print("Connection closed with {}:{}".format(client_address[0], client_address[1]))

def main():
    # Create a socket object
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the host and port
    sock.bind((host, port))

    # Listen for incoming connections
    sock.listen(5)

    print("Server is listening on {}:{}".format(host, port))

    while True:
        # Accept a connection from a client
        client_socket, client_address = sock.accept()
        print("Connected to {}:{}".format(client_address[0], client_address[1]))

        data = client_socket.recv(1024)
        if not data:
            break

        try:
            bar_pressure = float(data.decode())
            atm_pressure = bar_to_atm(bar_pressure)
            client_socket.send(str(atm_pressure).encode())
        except ValueError:
            client_socket.send(b"Invalid Input")

        client_socket.close()
            


if __name__ == '__main__':
    main()
