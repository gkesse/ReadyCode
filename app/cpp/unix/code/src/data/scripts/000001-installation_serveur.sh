#================================================
# installation_serveur
#================================================
echo "debut installation du serveur...........: OK"
#
GSRC_FILE=${GPROJECT_BUILD}/bin/rdcpp.exe
GDST_FILE=${GPROJECT_SERVER}/server
#
cp -p ${GSRC_FILE} ${GDST_FILE}
#
echo "fin installation du serveur.............: OK"
