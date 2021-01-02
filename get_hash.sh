#!/bin/bash

cat <<EOF
const char GitHash[] = "`git describe --always --abbrev=8`";
EOF
