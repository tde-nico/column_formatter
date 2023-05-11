#!/bin/bash

GREEN=$(tput setaf 10)
RED=$(tput setaf 9)
END=$(tput sgr0)

NAME="$1"

function test_failure {
	IFS=' ' read -ra test <<< "$@"
	"./$NAME" "${test[@]}" >/dev/null 2>/dev/null
	if [[ $? -eq 1 ]]; then
		echo "$GREEN[+] Success $@ $END"
	else
		echo "$RED[-] Failure $@ $END"
	fi
}

invalid_args=(
	""
	"a"
	"1"
	"a 1"
	"1 a"
	"1 1"
	"a 1 1"
	"1 a 1"
	"1 1 a"
	"-1 1 1"
	"1 -1 1"
	"1 1 -1"
	"1 1 1 a"
)

for arg in "${invalid_args[@]}"; do
	test_failure "$arg"
done


function test_cmd {
	eval "$@"
	if [[ $? -eq 0 ]]; then
		echo "$GREEN[+] Success $@ $END"
	else
		echo "$RED[-] Failure $@ $END"
	fi
}

valid_cmds=(
	"rm -f tmp.tmp ; ./$NAME 1 1 1 tests/test.txt tmp.tmp ; diff tmp.tmp tests/test_output.txt"
	"rm -f tmp.tmp ; cat tests/test.txt | ./$NAME 1 1 1 > tmp.tmp ; diff tmp.tmp tests/test_output.txt"
	"rm -f tmp.tmp ; cat tests/test.txt | ./$NAME 1 1 1 > tmp.tmp ; diff tmp.tmp tests/test_output.txt"
)

for cmd in "${valid_cmds[@]}"; do
	test_cmd "$cmd"
done

rm -f tmp.tmp
