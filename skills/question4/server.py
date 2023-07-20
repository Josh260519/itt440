import socket
import threading
import random

host = '192.168.17.128'
port = 8888



# Quotes
quotes = ["People often say that motivation doesn't last. Well, neither does bathing -- that's why we recommend it daily.",
          "Hire character. Train skill.", "Your time is limited, so don't waste it living someone else's life.",
          "If you cannot do great things, do small things in a great way.", "Without hustle, talent will only carry you so far.",
          "I'd rather regret the things I've done than regret the things I haven't done."]

def handle_client(client_socket, client_address):
    quote = random.choice(quotes)
    client_socket.send(quote.encode())
    client_socket.close()
    print("Connection closed with {}:{}".format(client_address[0], client_address[1]))

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Bind socket to the port and host
    sock.bind((host, port))

    sock.listen(5)

    print("QOTD Server is listening on  {}:{}".format(host, port))

    try:
        while True:
            client_socket, client_address = sock.accept()
            print("Connected to {}:{}".format(client_address[0], client_address[1]))

            # Create thread
            client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
            client_thread.start()

    except KeyboardInterrupt:
        print("\nServer is closed")


if __name__ == '__main__':
    main()


