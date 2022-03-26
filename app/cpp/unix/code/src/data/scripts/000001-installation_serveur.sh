#================================================
# installation_serveur
#================================================
echo "demarrage de l'installation du serveur..."
GSRC_FILE=${GPROJECT_BUILD}/bin/rdcpp.exe
GDST_FILE=${GPROJECT_SERVER}/server
cp -p ${GSRC_FILE} ${GDST_FILE}
echo "fin de l'installation du serveur..."
