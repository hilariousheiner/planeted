#!/usr/bin/env bash

set -uo pipefail

echo "Running tests..."

for input in *.pdsl; do
    echo "  $(basename "$input")"
    ../bin/Debug/planeted.exe "$input" output/
done

echo
echo "Comparing outputs..."

passed=0
failed=0

for reference in ref/*; do
    name=$(basename "$reference")
    outfile="output/$name"
	
	if [[ ! -f "$outfile" ]]; then
        echo "FAIL: file $name not generated"
        ((failed++))
        continue
    fi
	
	if diff -u "$reference" "$outfile"; then
        echo "PASS: $name"
        ((passed++))
    else
        echo "FAIL: $name"
        ((failed++))
    fi
done

echo
echo "Summary"
echo "-------"
echo "Passed: $passed"
echo "Failed: $failed"

exit $(( failed > 0 ))