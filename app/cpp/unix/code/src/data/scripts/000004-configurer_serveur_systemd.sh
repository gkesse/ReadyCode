#================================================
# configurer_serveur_systemd
#================================================
echo "debut du demarrage du serveur.............: OK"
#
export "GPROJECT_DATA=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data"
export "GPROJECT_SERVER=${GPROJECT_DATA}/server"
export "GPROJECT_ENV=PROD"
#
cd ${GPROJECT_SERVER}
./server test socket/server/start
#
echo "fin du demarrage du serveur...............: OK"
