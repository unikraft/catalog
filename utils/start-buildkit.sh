#!/bin/sh

# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2023, Unikraft GmbH and The Unikraft Authors.
#
# Start BuildKit as a container if not already started.
# BuildKit is used by KraftKit when building the root filesystem
# from a Dockerfile.
# 
# This script MUST be sourced (i.e. use `source start-buildkit.sh`).

# Variable used by KraftKit, hence the requirement for sourcing the script
export KRAFTKIT_BUILDKIT_HOST=docker-container://buildkitd

# Install container if not already installed.
docker container inspect buildkitd > /dev/null 2>&1
if test $? -eq 0; then
    echo "Container 'buidlkitd' is already installed. Nothing to do."
else
    echo "Installing 'buildkitd' container ... "
    docker run -d --name buildkitd --privileged moby/buildkit:latest
    exit $?
fi

test "$(docker container inspect -f '{{.State.Running}}' buildkitd 2> /dev/null)" = "true"
if test $? -eq 0; then
    echo "Container 'buidlkitd' is already running. Nothing to do."
else
    echo "Starting 'buildkitd' container ... "
    docker start buildkitd
    exit $?
fi
