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
	"a 1 1 1"
	"1 a 1 1"
	"1 1 a 1"
	"1 1 1 a"
	"-1 1 1 1"
	"1 -1 1 1"
	"1 1 -1 1"
	"1 1 1 -1"
	"1 1 1 1 a"
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

TMP="tmp.tmp"
RM="rm -f $TMP"
EARGS="3 40 20 5"
EXAMPLE="tests/example.txt"
DIFF="diff $TMP tests/example_output.txt"

valid_cmds=(
	"$RM ; ./$NAME $EARGS $EXAMPLE $TMP ; $DIFF"
	"$RM ; cat $EXAMPLE | ./$NAME $EARGS > $TMP ; $DIFF"
	"$RM ; cat $EXAMPLE | ./$NAME $EARGS > $TMP ; $DIFF"
)

for cmd in "${valid_cmds[@]}"; do
	test_cmd "$cmd"
done

rm -f tmp.tmp
