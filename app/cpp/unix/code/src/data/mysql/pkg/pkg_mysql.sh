#!/bin/bash
#================================================
GCONFIG=$GCONF/pkg_config.cnf
#================================================
ps_sql() {
    mysql --defaults-extra-file=$GCONFIG -Bse "$1"
}
#================================================
ps_sql_db() {
    echo "==> 1 : $1"
    echo "==> 2 : $2"
    #mysql --defaults-extra-file=$GCONFIG "$1" -Bse "$2"
}
#================================================
