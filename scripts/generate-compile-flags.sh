#!/usr/bin/env bash
set -euo pipefail

DEST="$ROOT/compile_flags.txt"

{
	cat <<EOF
-U__block
-isystem/opt/homebrew/include
-D__float128=long double
EOF

	"$GXX" -v -E -x c++ /dev/null -o /dev/null 2>&1 1>/dev/null \
		| grep -E '^[[:space:]][^[:space:]]+$$' \
		| xargs -n1 -I{} echo "-isystem{}"

	cat <<EOF
-DETHANKIM8683
-I$ROOT/include
-std=c++26
EOF
} > "$DEST"
