#!/usr/bin/env bash

set -eu

export TIME="Tardó: %Us - Consumió: %M KiB"
PROGRAMA="$1"
RET=0

# Correr con diff y sin Valgrind.
echo "Ejecución de pruebas unitarias de bf:"
echo ""
for x in *.test; do
    b=${x%.test}
    printf "${b} "
    cat ${b}.test
    ($PROGRAMA ${b}_script < ${b}_in > tmp_out 2> tmp_err; \
        python3 csvdiff.py ${b}_out tmp_out && 
        python3 csvdiff.py errGeneral_err tmp_err && \
        echo "OK") || { RET=$?; echo "ERROR"; }
done

# Salir si hubo errores de diff.
if [[ $RET -ne 0 ]]; then
    exit $RET
fi

echo ""
echo "Ejecución de pruebas con Valgrind:"
echo ""
# Correr con Valgrind y sin diff.
for x in *_in; do
    b=${x%_in}
    printf "${b} "
    cat ${b}.test
    valgrind --quiet --leak-check=full --track-origins=yes --error-exitcode=2 \
        $PROGRAMA <${b}_in >/dev/null && \
        echo "OK" || { RET=$?; echo "ERROR"; }
done

exit $RET
