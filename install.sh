mkdir -p appspace
mkdir -p appspace/client
mkdir -p appspace/server1
mkdir -p appspace/server2
mkdir -p appspace/server3

cp bin/client server.config appspace/client/
cp bin/server server.config appspace/server1/
cp bin/server server.config appspace/server2/
cp bin/server server.config appspace/server3/
