#!/usr/bin/env bash
set -euo pipefail

SRC="$ROOT/library"
DEST="$ROOT/snippets/cpp.lua"

mkdir -p "$(dirname "$DEST")"
{
	echo "return {"
	shopt -s globstar nullglob
	for f in "$SRC"/**/*.{h,c,hpp,cpp}; do
		[[ "$f" == **/.agents/** ]] && continue
		[[ "$f" == **/contest/** ]] && continue
		rel="${f#"$SRC"/}"
		echo "s(\"$rel\",{t({$(sed 's/\\/\\\\/g; s/"/\\"/g; s/.*/"&"/' "$f" | paste -sd, -)})}),"
	done
	echo "}"
} > "$DEST"
