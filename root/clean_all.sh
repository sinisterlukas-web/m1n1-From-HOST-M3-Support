#!/bin/bash
# clean_all.sh - Wipes build artifacts and resets the 'buckets'

echo "Cleaning project..."
rm -rf build/
rm -f dtbucket/*.dtb
# Optional: Keep the READMEs but clear the big binaries
find linuxbucket/ -type f ! -name 'README.md' -delete 
echo "Project cleaned. Ready for a fresh build or push."
