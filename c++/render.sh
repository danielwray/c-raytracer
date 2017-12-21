#!/bin/bash

main() {
    make
    if [[ ! ${?} == "0" ]]; then
        echo "There was an error running the 'make' command!"
        exit 1
    else
        ./c-tracer > rendered.ppm
	echo "Open rendered.ppm to see the rendered image."
    fi
}

main
