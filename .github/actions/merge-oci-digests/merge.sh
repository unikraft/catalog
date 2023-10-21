#!/usr/bin/env bash

DIGESTDIR=${1:-_oci}
OUTDIR=${2:-_out}
NAME=${3:-}

if [[ ${NAME} == "" ]]; then
  echo "cannot merge without setting name"
  exit 1
fi

set -xe;

sudo apt-get -qq update;
sudo apt-get -qq install -y --no-install-recommends jq file;

file --version;
jq --version;

REF="$(cut -d':' -f1 <<<"$NAME")"
TAG="$(cut -d':' -f2 <<<"$NAME")"

mkdir -p ${OUTDIR}/digests/sha256
mkdir -p ${OUTDIR}/indexes/${REF}

INDEX=

for DIR in $DIGESTDIR/*; do
  if [[ ! -d $DIR/sha256 ]]; then continue; fi

  # Find the index and either save the entire index if `INDEX` is unset,
  # otherwise simply copy all the manifests over to the existing `INDEX`
  for DIGEST in $DIR/sha256/*; do
    if ! [[ $(file ${DIGEST} | grep "JSON") ]]; then
      cp ${DIGEST} ${OUTDIR}/digests/sha256
      continue;
    fi
    if ! [[ $(cat ${DIGEST} | jq 'has("mediaType")') ]]; then
      cp ${DIGEST} ${OUTDIR}/digests/sha256
      continue;
    fi
    _MEDIATYPE=$(cat ${DIGEST} | jq -r .mediaType)
    if [[ ${_MEDIATYPE} != "application/vnd.oci.image.index.v1+json" ]]; then
      cp ${DIGEST} ${OUTDIR}/digests/sha256
      continue;
    fi

    # No index has yet been determined, use this as the base.  First, copy it to
    # a new place
    if [[ ${INDEX} == "" ]]; then
      INDEX=${OUTDIR}/indexes/${REF}/${TAG}
      cp $DIGEST $INDEX

    # An index has already been found, update the existing index and remove this
    # digest.
    else
      _V=$(echo -n -e "$(cat ${INDEX})\n$(cat ${DIGEST})" | jq -s '.[0].manifests=([.[].manifests]|flatten)|.[0]')
      echo "${_V}" > ${INDEX}
    fi
  done
done
