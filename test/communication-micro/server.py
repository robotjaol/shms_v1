import socket

server_ip = "10.17.38.137"
server_port = 5000

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((server_ip, server_port))

print(f"Server UDP berjalan di IP {server_ip} dan port {server_port}. Menunggu data...")

while True:
    try:
        data, client_address = server_socket.recvfrom(1024)
        print(f"Data diterima dari {client_address}: {data.decode('utf-8')}")
    except KeyboardInterrupt:
        print("\nServer dihentikan.")
        break
    except Exception as e:
        print(f"Error: {e}")
        break

server_socket.close()

# import socket

# # Tentukan alamat IP dan port yang digunakan oleh server
# server_ip = "192.168.146.100"  # IP LAPTOP
# server_port = 5000  # PORT ESP32 DAN LAPTOP

# server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# server_socket.bind((server_ip, server_port))

# print(f"Server UDP berjalan di IP {server_ip} dan port {server_port}. Menunggu pesan dari ESP32...")

# while True:
#     try:
#         data, client_address = server_socket.recvfrom(1024)  # buffer size 1024 bytes
#         print(f"Data diterima dari {client_address}: {data.decode('utf-8')}")
#     except KeyboardInterrupt:
#         print("\nServer dihentikan.")
#         break
#     except Exception as e:
#         print(f"Error: {e}")
#         break

# server_socket.close()


# import socket

# # server_ip = "192.168.146.100"  # IP Address laptop Anda
# server_ip = "10.17.38.137"
# server_port = 5000  # Port yang sama dengan yang digunakan di client ESP32

# # Membuat socket TCP
# server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# server_socket.bind((server_ip, server_port))  # Mengikat socket ke alamat IP dan port
# server_socket.listen(1)  # Mendengarkan koneksi masuk (dengan 1 koneksi dalam antrian)

# print(f"Server TCP berjalan di IP {server_ip} dan port {server_port}. Menunggu koneksi...")

# client_socket, client_address = server_socket.accept()
# print(f"Koneksi diterima dari {client_address}")

# while True:
#     try:
#         data = client_socket.recv(1024)  # Buffer size 1024 bytes
#         if not data:
#             print("Koneksi terputus dari client.")
#             break
#         print(f"Data diterima dari {client_address}: {data.decode('utf-8')}")
#     except KeyboardInterrupt:
#         print("\nServer dihentikan.")
#         break
#     except Exception as e:
#         print(f"Error: {e}")
#         break

# client_socket.close()
# server_socket.close()

