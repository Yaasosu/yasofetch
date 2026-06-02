#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
SCRIPT_PATH="$SCRIPT_DIR/venv/bin/python $SCRIPT_DIR/yasofetch.py"
  if [[ "$SHELL" == *"fish"* ]]; then

  # Fish
  mkdir -p ~/.config/fish/functions
  echo "function fetchPy; $SCRIPT_PATH; end" > ~/.config/fish/functions/fetchPy.fish
  elif [ -f "$HOME/.zshrc" ]; then

  # Zsh
  echo "alias fetchPy='$SCRIPT_PATH'" >> ~/.zshrc
  source ~/.zshrc
  else

  # Bash
  echo "alias fetchPy='$SCRIPT_PATH'" >> ~/.bashrc
  source ~/.bashrc

fi
echo "Готово! Теперь просто запускай: fetchPy"
