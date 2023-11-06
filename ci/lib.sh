#!/bin/sh -xe
# Copyright 2023(c) Analog Devices, Inc.
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#     - Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     - Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in
#       the documentation and/or other materials provided with the
#       distribution.
#     - Neither the name of Analog Devices, Inc. nor the names of its
#       contributors may be used to endorse or promote products derived
#       from this software without specific prior written permission.
#     - The use of this software may or may not infringe the patent rights
#       of one or more patent holders.  This license does not release you
#       from the requirement that you obtain separate licenses from these
#       patent holders to use this software.
#     - Use of the software either in source or binary form, must be run
#       on or directly connected to an Analog Devices Inc. component.
#
# THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
# INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A
# PARTICULAR PURPOSE ARE DISCLAIMED.
#
# IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, INTELLECTUAL PROPERTY
# RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
# BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
# THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#List of excluded driver folders for the documentation generation.

COMMON_SCRIPTS="astyle.sh astyle_config cppcheck.sh"
NUM_JOBS=$(nproc)

get_script_path() {
	local script="$1"

	[ -n "$script" ] || return 1

	if [ -f "ci/$script" ] ; then
		echo "ci/$script"
	elif [ -f "build/$script" ] ; then
		echo "build/$script"
	else
		return 1
	fi
}

command_exists() {
	local cmd=$1
	[ -n "$cmd" ] || return 1
	type "$cmd" >/dev/null 2>&1
}

ensure_command_exists() {
	local cmd="$1"
	local package="$2"
	[ -n "$cmd" ] || return 1
	[ -n "$package" ] || package="$cmd"
	! command_exists "$cmd" || return 0
	# go through known package managers
	for pacman in apt-get brew yum ; do
		command_exists $pacman || continue
		$pacman install -y $package || {
			# Try an update if install doesn't work the first time
			$pacman -y update && \
				$pacman install -y $package
		}
		return $?
	done
	return 1
}

ensure_command_exists sudo

echo_red() { printf "\033[1;31m$*\033[m\n"; }
echo_green() { printf "\033[1;32m$*\033[m\n"; }

# Other scripts will download lib.sh [this script] and lib.sh will
# in turn download the other scripts it needs.
# This gives way more flexibility when changing things, as they propagate
download_common_scripts() {
	for script in $COMMON_SCRIPTS ; do
		[ ! -f "ci/$script" ] || continue
		[ ! -f "build/$script" ] || continue
		mkdir -p build
		ensure_command_exists wget
		wget https://raw.githubusercontent.com/analogdevicesinc/no-OS/master/ci/$script \
			-O build/$script
	done
}

download_common_scripts
