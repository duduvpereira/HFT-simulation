<h1 align="center"> A Simulation Platform for Assessment of Market Strategies Based on the PUMA Trading System </h1>


To run, compile the 3 files:

gcc client.c -o client
gcc client_2.c -o client_2
gcc gateway.c -o gateway
gcc matchingEngine.c -o matchingEngine

After that, just execute in order:
gateway -> client (order independent) -> matchingEngine

To add more participants follow the steps below:

Replicate the client code and on line 258 modify the port:
serv_addr.sin_port = htons([PORT]);

And in matchingEngine.c put a new sending line with the new port added on the client.
