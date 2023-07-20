import socket


def main():
    # Prompt the user for server IP address and port number
    server_ip = input("Enter the server IP address: ")
    server_port = int(input("Enter the server port number: "))

    # Creates a socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    server_address = (server_ip, server_port)
    client_socket.connect(server_address)import socket


def main():
    # Prompt the user for server IP address and port number
    server_ip = input("Enter the server IP address: ")
    server_port = int(input("Enter the server port number: "))

    # Creates a socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    server_address = (server_ip, server_port)
    client_socket.connect(server_address)

    while True:
        
        # Ask the user for input
        user_input = input("Enter 1 to get a Quote of the Day and anything else except 1 to quit: ")

        # Breaks the loop if anything other than 1 is entered
        if user_input != '1':
            break
        
        # Send user input
        client_socket.sendall(user_input.encode())

        #Receive quote from server
        quote = client_socket.recv(4096).decode()
        print(f"({quote})")


    # Close the connection
    client_socket.close()

if __name__ == "__main__":
    main()
    
