#================================================
# utiliser_nohup
#================================================

# ressources
https://askubuntu.com/questions/8653/how-to-keep-processes-running-after-ending-ssh-session#:~:text=ssh%20into%20your%20remote%20box,but%20leave%20your%20processes%20running.
https://linux.die.net/man/1/nohup

# role
->  continuer a executer un programme apres deconnexion

# afficher l'aide
nohup --help

# afficher la version
nohup --version

# executer un programme
nohup /home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/scripts/000002-demarrer_serveur.sh

# executer un programme en tache de fond
nohup /home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/scripts/000002-demarrer_serveur.sh &

# afficher les programmes
top
=====>
    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
  59422 gkesse    20   0   12608   3404   2796 R   1,3   0,0   0:10.50 top
    784 root      20   0 1094072  36836  17648 S   1,0   0,5   0:11.29 snapd
  52681 gkesse    20   0    9444   3232   2968 S   1,0   0,0   0:15.65 bash
    991 mysql     20   0 2179148 400744  31028 S   0,3   5,0   2:38.65 mysqld
   1562 gkesse    20   0  379268   5092   4552 S   0,3   0,1   0:01.92 gvfsd-f+
  48498 gkesse    20   0  122952   6860   5980 S   0,3   0,1   1:56.26 server
  51235 gkesse    20   0  254564   7012   6096 S   0,3   0,1   1:46.97 server
  52618 gkesse    20   0   17064   5648   4260 S   0,3   0,1   0:05.78 sshd
  56880 root      20   0       0      0      0 I   0,3   0,0   0:00.53 kworker+
  61179 root      20   0       0      0      0 I   0,3   0,0   0:00.08 kworker+
=====>
    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
  64828 gkesse    20   0   12608   3300   2692 R  27,8   0,0   0:00.09 top
   1121 gdm       20   0 3549616 165024  93560 S  16,7   2,1   0:46.28 gnome-s+
      1 root      20   0  167428  12012   7092 S   0,0   0,2   0:09.58 systemd
      2 root      20   0       0      0      0 S   0,0   0,0   0:00.13 kthreadd
      3 root       0 -20       0      0      0 I   0,0   0,0   0:00.00 rcu_gp
      4 root       0 -20       0      0      0 I   0,0   0,0   0:00.00 rcu_par+
=====>
  67984 gkesse    20   0   12608   3400   2796 R   1,0   0,0   0:00.16 top
    991 mysql     20   0 2179148 400744  31028 S   0,7   5,0   2:41.95 mysqld
  67937 gkesse    20   0    9444   3096   2832 S   0,7   0,0   0:00.07 bash
  66064 root      20   0       0      0      0 I   0,3   0,0   0:00.02 kworker+
  67927 gkesse    20   0   17064   5688   4288 S   0,3   0,1   0:00.04 sshd
      1 root      20   0  167428  12012   7092 S   0,0   0,2   0:09.73 systemd
=====>
  69052 gkesse    20   0   12608   3224   2612 R   1,3   0,0   0:00.25 top
   1121 gdm       20   0 3549624 165052  93572 S   1,0   2,1   0:47.45 gnome-shell
  67937 gkesse    20   0    9444   3096   2832 S   1,0   0,0   0:01.57 bash
    991 mysql     20   0 2179148 400744  31028 S   0,7   5,0   2:42.84 mysqld
  67927 gkesse    20   0   17064   5688   4288 S   0,3   0,1   0:00.60 sshd
  68499 gkesse    20   0  196772   7048   6156 S   0,3   0,1   0:00.42 server
      1 root      20   0  167428  12012   7092 S   0,0   0,2   0:09.75 systemd
      2 root      20   0       0      0      0 S   0,0   0,0   0:00.13 kthreadd
      3 root       0 -20       0      0      0 I   0,0   0,0   0:00.00 rcu_gp
      4 root       0 -20       0      0      0 I   0,0   0,0   0:00.00 rcu_par_gp

# tuer un programme
kill -9 51235
kill -9 48498





