import socket, select, sys, queue, pars, json
from queue import Queue

def input_serv_port():
    data = input()
    if data == "exit":
        return
    return data
restaurant_list = 0
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setblocking(0)
while True:
    try:
        TCP_PORT = int(input_serv_port())
        sock.bind(("", TCP_PORT))
        break
    except:
        print("error input")

sock.listen(10)
inputs = [ sock ]
outputs = [ ]

message_queues = {}

def server_socket_parse(sock):
    diction = {"ip": sock.getpeername()[0], "port": sock.getpeername()[1]}
    return diction


def server_info(inputs, client):
    sock_list = []

    for i in inputs:
        if i != inputs[0]:
            sock_list.append(server_socket_parse(i))

    message = json.dumps(sock_list, sort_keys=True, indent=4)
    client.send(message.encode('utf-8'))


def mainf():
    while True:
        readable, writable, exceptional = select.select(inputs, outputs, inputs, 0.05)

        for client in readable:
            if client is sock:
                connection, client_address = client.accept()
                connection.setblocking(0)
                inputs.append(connection)

                message_queues[connection] = Queue()
            else:
                data = client.recv(1024)
                if data:
                    print("<<<", data.decode("utf-8"))
                    if (data.decode("utf-8").find("exit") != -1):
                        client.send("HTTP/1.1 200 OK\nContent-type:text\nContent-length: 17\n\r\n\rExit successful!".encode('utf-8'))
                        return
                    message_queues[client].put(data)
                    if client not in outputs:
                        outputs.append(client)
                else:
                    if client in outputs:
                        outputs.remove(client)
                    inputs.remove(client)
                    client.close()
                    del message_queues[client]

        for client in writable:
            if dict.__len__(message_queues) > 0:
                if message_queues.get(client):
                    try:
                        next_msg = message_queues[client].get_nowait()
                    except queue.Empty:
                        outputs.remove(client)
                    else:
                        if(next_msg.decode('utf-8') == "info"):
                            server_info(inputs,client)
                        client.send(pars.getJson(next_msg.decode('utf-8')).encode('utf-8'))


        for client in exceptional:
            inputs.remove(client)
            if client in outputs:
                outputs.remove(client)
            client.close()
            del message_queues[client]
mainf();
