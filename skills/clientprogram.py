import socket

# Enter the server address instructed by lecturer and the port number
server_ip = input("Enter the server IP address: ")
server_port = int(input("Enter the server port number: "))

# To create a socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# To connect to the server
server_address = (server_ip, server_port)
client_socket.connect(server_address)

# looping may not be necessary but to ensure the link is received, looping was implemented as a backup feature
while True:
    # Prompt the user for input
    user_input = input("Enter a string (or press 'Q' to quit): ")

    # Break the loop if 'Q' or 'q' is entered
    # lower() to ignore case sensitivity
    if user_input.lower() == 'q':
        break

    # Sending input to server
    client_socket.sendall(user_input.encode('utf-8'))

    # Receiving the user input from server
    # It is required to be able to receive the skill assessment link
    reply = client_socket.recv(1024).decode('utf-8')

    # To get our link for the skill assess test
    print("Reply from server:", reply)

# Close the connection
client_socket.close()
