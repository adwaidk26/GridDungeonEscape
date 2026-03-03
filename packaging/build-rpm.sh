#!/bin/bash

# A script to automate the RPM build process for GridDungeonEscape.
#
# This script will:
# 1. Create a source tarball from the current git HEAD.
# 2. Set up the standard rpmbuild directory structure.
# 3. Copy the source and spec files to the correct locations.
# 4. Install all necessary build dependencies.
# 5. Run the rpmbuild command.

# Exit immediately if any command fails
set -e

# --- Configuration ---
# Get project root and spec file location dynamically
PROJECT_ROOT=$(git rev-parse --show-toplevel)
SPEC_FILE="${PROJECT_ROOT}/packaging/GridDungeonEscape.spec"
SPEC_FILENAME=$(basename "${SPEC_FILE}")

# Read Name and Version directly from the spec file to avoid hardcoding
NAME=$(rpmspec -q --qf "%{name}" "${SPEC_FILE}")
VERSION=$(rpmspec -q --qf "%{version}" "${SPEC_FILE}")
ARCHIVE_NAME="${NAME}-${VERSION}.tar.gz"

echo "--- Building RPM for ${NAME}-${VERSION} ---"

# 1. Create Source Archive in a temporary location
echo "--> Creating source archive from git..."
cd "${PROJECT_ROOT}"
git archive --format=tar --prefix="${NAME}-${VERSION}/" HEAD | gzip > "/tmp/${ARCHIVE_NAME}"

# 2. Set up RPM Build Environment
echo "--> Setting up RPM build environment in ~ ..."
rpmdev-setuptree

# 3. Place Files
echo "--> Copying source archive and spec file..."
mv "/tmp/${ARCHIVE_NAME}" "${HOME}/rpmbuild/SOURCES/"
cp "${SPEC_FILE}" "${HOME}/rpmbuild/SPECS/"

# 4. Install Build Dependencies
echo "--> Installing build dependencies (sudo required)..."
sudo dnf builddep -y "${HOME}/rpmbuild/SPECS/${SPEC_FILENAME}"

# 5. Build RPM
echo "--> Building RPMs..."
rpmbuild -ba "${HOME}/rpmbuild/SPECS/${SPEC_FILENAME}"

echo -e "\n✅ RPM build complete! Packages are located in ~/rpmbuild/RPMS and ~/rpmbuild/SRPMS"