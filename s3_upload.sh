#!/bin/bash
set -eo pipefail

s3_upload() {
  local filepath=$1
  local content_type=$2
  if [[ -n $DRYRUN ]]; then
    echo "filepath:$filepath content_type:$content_type"
  else
    aws s3 cp "./$filepath" "s3://hackernewsmobile.com/$filepath" --content-type "$content_type"
  fi
}

s3_sync() {
  local filepath=$1
  if [[ -f $filepath ]]; then
    local filename=$(basename "$filepath")
    local extension=$(node -e "process.stdout.write(require('path').extname('$filename'))")
    if [[ -z "$extension" ]]; then
      s3_upload "$filepath" 'text/html'
    elif [[ "$extension" == '.html' ]]; then
      s3_upload "$filepath" 'text/html'
    elif [[ "$extension" == '.js' ]]; then
      s3_upload "$filepath" 'application/javascript'
    elif [[ "$extension" == '.css' ]]; then
      s3_upload "$filepath" 'text/css'
    elif [[ "$extension" == '.png' ]]; then
      s3_upload "$filepath" 'image/png'
    elif [[ "$extension" == '.gif' ]]; then
      s3_upload "$filepath" 'image/gif'
    elif [[ "$extension" == '.jpg' ]]; then
      s3_upload "$filepath" 'image/jpeg'
    fi
  fi
}



for filepath in public/*
do
  cp "$filepath" dist
done

cd dist

for filepath in *
do
  s3_sync "$filepath"
done

for filepath in build/*
do
  s3_sync "$filepath"
done
