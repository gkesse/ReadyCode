#================================================
# demarrer_serveur_crontab
#================================================
echo "debut du demarrage du serveur.............: OK"
#
export "GPROJECT_ROOT=/home/gkesse/Programs"
export "GPROJECT_PATH=${GPROJECT_ROOT}/ReadyCode"
export "GPROJECT_UNIX=${GPROJECT_PATH}/app/cpp/unix"
export "GPROJECT_BUILD=${GPROJECT_UNIX}/unix"
export "GPROJECT_SRC=${GPROJECT_UNIX}/code/src"
export "GPROJECT_DATA=${GPROJECT_SRC}/data"
export "GPROJECT_TMP=${GPROJECT_DATA}/tmp"
export "GPROJECT_SCRIPTS=${GPROJECT_DATA}/scripts"
export "GPROJECT_SERVER=${GPROJECT_DATA}/server"
export "GPROJECT_ENV=PROD"
#
cd ${GPROJECT_SERVER}
./server test socket/server/start
#
echo "fin du demarrage du serveur...............: OK"
