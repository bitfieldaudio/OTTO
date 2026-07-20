#!/usr/bin/env bash
# Bundle build/bin/otto into dist/OTTO.app for Finder launch.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
BIN="$ROOT/build/bin/otto"
APP="$ROOT/dist/OTTO.app"
CONTENTS="$APP/Contents"
MACOS="$CONTENTS/MacOS"
RES="$CONTENTS/Resources"

if [[ ! -x "$BIN" ]]; then
  echo "Missing $BIN — run: just build otto_exec" >&2
  exit 1
fi

rm -rf "$APP"
mkdir -p "$MACOS" "$RES"

cp "$BIN" "$MACOS/OTTO"
chmod +x "$MACOS/OTTO"
cp -R "$ROOT/resources" "$RES/resources"
cp -R "$ROOT/data" "$RES/data"
if [[ -f "$ROOT/ottoconf.mac.json" ]]; then
  cp "$ROOT/ottoconf.mac.json" "$RES/ottoconf.json"
fi

# Launcher sets cwd to Resources so ./data and ./resources resolve.
cat > "$MACOS/otto-launch" <<'EOF'
#!/bin/bash
DIR="$(cd "$(dirname "$0")" && pwd)"
RES="$(cd "$DIR/../Resources" && pwd)"
cd "$RES"
exec "$DIR/OTTO" -e -d "$RES/data" -r "$RES/resources" -c "$RES/ottoconf.json" "$@"
EOF
chmod +x "$MACOS/otto-launch"

cat > "$CONTENTS/Info.plist" <<'EOF'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleName</key>
  <string>OTTO</string>
  <key>CFBundleDisplayName</key>
  <string>OTTO</string>
  <key>CFBundleIdentifier</key>
  <string>com.bitfieldaudio.otto.desktop</string>
  <key>CFBundleVersion</key>
  <string>0.0.1</string>
  <key>CFBundleShortVersionString</key>
  <string>0.0.1</string>
  <key>CFBundleExecutable</key>
  <string>otto-launch</string>
  <key>CFBundlePackageType</key>
  <string>APPL</string>
  <key>LSMinimumSystemVersion</key>
  <string>12.0</string>
  <key>NSHighResolutionCapable</key>
  <true/>
  <key>NSMicrophoneUsageDescription</key>
  <string>OTTO uses audio input when a duplex device is selected.</string>
</dict>
</plist>
EOF

echo "Built $APP"
echo "Open with: open \"$APP\""
