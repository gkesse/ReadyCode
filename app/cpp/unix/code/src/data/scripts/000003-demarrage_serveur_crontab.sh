#================================================
# demarrage_serveur_crontab
#================================================
echo "debut du demarrage du serveur.............: OK"
#
GPROJECT_PATH=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data
GPROJECT_SERVER=${GPROJECT_PATH}/server
#
cd ${GPROJECT_SERVER}
./server test socket/server/start
#
echo "fin du demarrage du serveur...............: OK"
