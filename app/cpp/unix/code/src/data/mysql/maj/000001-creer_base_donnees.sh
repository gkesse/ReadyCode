#================================================
# creer_base_donnees
#================================================
echo "debut installation du serveur...........: OK"
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
GSRC_FILE=${GPROJECT_BUILD}/bin/rdcpp.exe
GDST_FILE=${GPROJECT_SERVER}/server
#
cp -p ${GSRC_FILE} ${GDST_FILE}
#
echo "fin installation du serveur.............: OK"
