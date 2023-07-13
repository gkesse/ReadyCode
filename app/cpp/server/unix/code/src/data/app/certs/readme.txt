
#================================================
# ca root
#================================================

mkdir -p ca/private

openssl req \
-x509 \
-nodes \
-days 3650 \
-newkey rsa:4096 \
-keyout ca/private/ca_key.pem \
-out ca/ca_cert.pem \
-subj "/C=FR/ST=Bas-Rhin State/L=Strasbourg City/O=ReadyDev Inc./CN=readydev.ovh"

tree

#================================================
# server private key
#================================================

mkdir -p server/private

openssl genrsa -out server/private/server_key.pem 4096

openssl req -new \
-key server/private/server_key.pem \
-out server/server.csr \
-subj "/C=FR/ST=Bas-Rhin State/L=Strasbourg City/O=ReadyDev Inc./CN=server.readydev.ovh"

#================================================
# client private key
#================================================

mkdir -p client/private

openssl genrsa -out client/private/client_key.pem 4096

openssl req -new \
-key client/private/client_key.pem \
-out client/client.csr \
-subj "/C=US/ST=Bas-Rhin State/L=Strasbourg City/O=ReadyDev Inc./CN=client.readydev.ovh"

openssl x509 -req -days 1460 -in server/server.csr \
-CA ca/ca_cert.pem -CAkey ca/private/ca_key.pem \
-CAcreateserial -out server/server_cert.pem

openssl x509 -req -days 1460 -in client/client.csr \
-CA ca/ca_cert.pem -CAkey ca/private/ca_key.pem \
-CAcreateserial -out client/client_cert.pem
