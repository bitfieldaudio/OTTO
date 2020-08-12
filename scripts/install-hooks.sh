#!/bin/bash

(cat > .git/hooks/pre-commit) <<EOF
#!/bin/bash

format_file() {
    file="${1}"
  if [ -f $file ]; then
    clang-format -i ${STYLEARG} ${1}
    git add ${1}
  fi
}

case "${1}" in
  --about )
    echo "Runs clang-format on source files"
    ;;
  * )
    for file in `git diff-index --cached --name-only HEAD | grep -iE '\.(cpp|cc|h|hpp)' ` ; do
      format_file "${file}"
    done
    ;;
esac
EOF
