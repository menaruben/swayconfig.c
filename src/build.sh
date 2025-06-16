#!/bin/bash
set -euo pipefail

SRC="swayconfig.c"
BIN="./swayconfig"
CONFIG_DIR="${HOME}/.config/sway"
BACKUP_DIR="${CONFIG_DIR}/backups"
CONFIG="${CONFIG_DIR}/config"
BACKUP="${BACKUP_DIR}/config.$(date +%s).backup"

echo "Compiling $SRC..."
if ! gcc -Wall -Wextra -o "$BIN" "$SRC"; then
  echo "Compilation failed with exit code $?."
  exit 1
fi
echo "Compilation successful."

# Ensure the backup directory exists
mkdir -p "$BACKUP_DIR"

if [[ -f "$CONFIG" ]]; then
  echo "Backing up current config to $BACKUP..."
  cp "$CONFIG" "$BACKUP"
else
  echo "No existing config file to backup."
fi

echo "Running $BIN and writing output to $CONFIG..."
./"$BIN" > "$CONFIG"

echo "Removing executable $BIN..."
rm -f "$BIN"

echo "Done! You can reload the config with:"
echo "  swaymsg reload"
