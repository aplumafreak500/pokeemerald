#!/bin/bash

cat <<EOF
const char BuildDateTime[] = "`date -u +"%Y %m %d %H:%M"`";
EOF
