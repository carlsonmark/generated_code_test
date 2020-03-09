#!/bin/bash
# Creates a generated.cmake file from the given filenames.
# The first argument is the CMakeLists.txt file to write to.
OUTFILE="${1}"/generated.cmake
shift

rm -f "$OUTFILE"

for f in "${@}"
do
cat >> "$OUTFILE" <<EOF
set (GENERATED_SOURCES \${GENERATED_SOURCES} $f)
EOF
done
