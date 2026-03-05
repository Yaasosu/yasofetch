#!/bin/bash

set -e

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
EXECUTABLE="yasofetch"
INSTALL_DIR="/usr/local/bin"

echo "🔨 Assembling: $EXECUTABLE..."
echo "   Project: $PROJECT_DIR"
echo "   Installing: $INSTALL_DIR/$EXECUTABLE"
echo ""

cd "$PROJECT_DIR"

# Очистка (если нужна)
# make clean

# Сборка
make -j"$(nproc)"

# Установка
echo ""
echo "🚀 Installing (maybe need for sudo)..."
sudo cp "$EXECUTABLE" "$INSTALL_DIR/$EXECUTABLE"
sudo chmod +x "$INSTALL_DIR/$EXECUTABLE"

echo ""
echo "✅ Succesfull! you can run yasofetch!: $EXECUTABLE"
