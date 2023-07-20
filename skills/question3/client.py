import socket


def conversion_input():
    while True:
        try:
            pressure = float(input("Enter pressure in bar: "))
            return pressure
        except ValueError:
            print("Invalid input. Please enter a valid number.")

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
        # Prompt the user for input
        pressure = conversion_input()
    
        # Send the user input to the server
        client_socket.send(str(pressure).encode())

        # Receive the atm pressure
        atmosphere_pressure = client_socket.recv(1024).decode()
        print(f"Pressure in atmosphere-standard: {atmosphere_pressure} atm")
    
    # Close the connection
    client_socket.close()

if __name__ == "__main__":
main()
