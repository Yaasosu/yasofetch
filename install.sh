#!/bin/sh

set -e

APP_NAME="yasofetch"
INSTALL_DIR="$HOME/.local/share/$APP_NAME"
BIN_DIR="$HOME/.local/bin"

echo "▶ Installing $APP_NAME..."

mkdir -p "$INSTALL_DIR"
mkdir -p "$BIN_DIR"

curl -fsSL https://raw.githubusercontent.com/Yaasosu/yasofetch/main/yasofetch.py \
  -o "$INSTALL_DIR/yasofetch.py"

curl -fsSL https://raw.githubusercontent.com/Yaasosu/yasofetch/main/distro_logo.py \
  -o "$INSTALL_DIR/distro_logo.py"

python3 -m pip install --user distro psutil uptime

cat > "$BIN_DIR/yasofetch" <<EOF
#!/bin/sh
python3 "$INSTALL_DIR/yasofetch.py"
EOF

chmod +x "$BIN_DIR/yasofetch"

echo "✔ Installed successfully!"
echo "👉 Run: yasofetch"