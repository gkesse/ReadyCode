#================================================
# demarrage_serveur_crontab
#================================================
echo "debut du demarrage du serveur.............: OK"
#
GSERVER=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/server
#
cd ${GSERVER}
./server test socket/server/start
#
echo "fin du demarrage du serveur...............: OK"
