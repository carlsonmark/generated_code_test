#!/bin/bash
# Simple code generator
# Creates a .cpp and .hpp file from the first argument in the directory
# given by the second argument
mkdir -p "${2}"


CPPNAME=$2/$(basename ${1/.in/.cpp})
cat "${1}" > "${CPPNAME}"

HPPNAME=$2/$(basename ${1/.in/.hpp})

cat > "${HPPNAME}" <<EOF
#include <string>
std::string $(basename ${1/.in/})();
EOF
