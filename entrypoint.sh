#!/bin/bash

SLEEPTIME=10
if [ $# == 0 ]; then
	echo "Please specify csv filename"
else
	CSV=$1
	URL=http://example.com/upload.php
	TOKEN=abcdef
	SLEEPTIME=10m
	echo "I will upload $CSV to $URL each $SLEEPTIME"
fi

get_temperature() {
	local OUTPUT="$(./tempered -c -2.5 ${@})"
	echo "$OUTPUT" >&2
	local temp=$(echo "$OUTPUT" | grep temperature | head -n1 | sed "s:.*temperature ::;s: °C::")
	if echo "$temp" | egrep '^-*[0-9]+\.[0-9]*$' >/dev/null; then
		echo $temp
		return 0
	fi
	return 1
}

while true; do
	temp=$(get_temperature)
	if [ ! $? == 0 ]; then
		exit $?
	fi
	if [ -n "$CSV" ]; then
		echo "$(date +%s);$temp" > /tmp/$CSV
		curl -s $URL -Ftoken=$TOKEN -Fcapteur=@/tmp/$CSV || echo "error sending /tmp/$CSV to $URL: $?"
	fi
	sleep $SLEEPTIME
done
