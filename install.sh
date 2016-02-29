rm -rf appspace*
mkdir appspace
mkdir appspace/client
mkdir appspace/server1
mkdir appspace/server2
mkdir appspace/server3

cp bin/client server.config appspace/client/
cp bin/server server.config appspace/server1/
cp bin/server server.config appspace/server2/
cp bin/server server.config appspace/server3/
