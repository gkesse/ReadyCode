# probleme
remote: Enumerating objects: 21, done.
remote: Counting objects: 100% (21/21), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 11 (delta 8), reused 11 (delta 8), pack-reused 0
error: insufficient permission for adding an object to repository database .git/objects
fatal: failed to write object
fatal: unpack-objects failed
make: *** [Makefile.cmd.mak:67: git_pull] Error 1

# resolution
cd ~/Programs/ReadyCode/
chown -R "${USER:-$(id -un)}" .
