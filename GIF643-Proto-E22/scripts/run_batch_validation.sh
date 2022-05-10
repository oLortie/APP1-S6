#!/usr/bin/env bash
# Assumes this is run in the build/ folder.

mkdir -p output

# Fichier valid.task
#time ../build/asset_conv 4 ../validation/valid.task

# Vérification MD5
time ../build/asset_conv 4 ../validation/valid.task
if md5sum --quiet -c ../validation/valid-docker.md5; then
    echo "OK"
    return 0
else
    return 1
fi
